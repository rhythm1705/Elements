#include "VulkanRenderContext.h"

#include "VulkanCommandBuffers.h"
#include "VulkanDevice.h"
#include "VulkanImage.h"
#include "VulkanRenderFrame.h"
#include "VulkanRenderTarget.h"
#include "VulkanSwapChain.h"

namespace Elements {
VulkanRenderContext::VulkanRenderContext(VulkanDevice &device, vk::SurfaceKHR surface, uint32_t width, uint32_t height) :
device{ device }, surfaceExtent{ width, height }, queue{ device.getGraphicsQueue() } {
    if (surface) {
        swapchain = std::make_unique<VulkanSwapchain>(device, surface);
    }
}

VulkanRenderContext::~VulkanRenderContext() {
}

VulkanDevice &VulkanRenderContext::getDevice() {
    return device;
}

vk::Format VulkanRenderContext::getFormat() {
    return swapchain->getSwapChainImageFormat();
}

VulkanSwapchain &VulkanRenderContext::getSwapchain() {
    return *swapchain;
}

vk::Extent2D VulkanRenderContext::getSurfaceExtent() const {
    return surfaceExtent;
}

uint32_t VulkanRenderContext::getActiveFrameIndex() const {
    return activeFrameIndex;
}

std::vector<std::unique_ptr<VulkanRenderFrame>> &VulkanRenderContext::getRenderFrames() {
    return frames;
}

void VulkanRenderContext::handleSurfaceChanges() {
    vk::SurfaceCapabilitiesKHR surfaceCapabilities
      = device.getPhysicalDevice().getSurfaceCapabilitiesKHR(swapchain->getSurface());
    if (surfaceCapabilities.currentExtent.width != surfaceExtent.width
        || surfaceCapabilities.currentExtent.height != surfaceExtent.height) {
        device.getHandle().waitIdle();
        updateSwapchain(surfaceCapabilities.currentExtent);
        surfaceExtent = surfaceCapabilities.currentExtent;
    }
}

void VulkanRenderContext::requestPresentMode(const vk::PresentModeKHR presentMode) {
}

void VulkanRenderContext::requestImageFormat(const vk::Format format) {
}

void VulkanRenderContext::setPresentModePriority(const std::vector<vk::PresentModeKHR> &presentModePriorityList) {
}

void VulkanRenderContext::setSurfaceFormatPriority(const std::vector<vk::SurfaceFormatKHR> &surfaceFormatPriorityList) {
}

void VulkanRenderContext::prepare() {
    device.getHandle().waitIdle();
    if (swapchain) {
        surfaceExtent = swapchain->getswapChainExtent();
        for (auto &image : swapchain->getSwapChainImages()) {
            auto swapchainImage
              = VulkanImage(device, image, surfaceExtent, swapchain->getSwapChainImageFormat());
            auto renderTarget = VulkanRenderTarget::createRenderTarget(std::move(swapchainImage));
            frames.emplace_back(std::make_unique<VulkanRenderFrame>(device, std::move(renderTarget)));
        }
    }
}

void VulkanRenderContext::updateSwapchain(const vk::Extent2D &extent) {
    device.clearFramebuffers();
    swapchain = std::make_unique<VulkanSwapchain>(device, swapchain->getSurface());
}

void VulkanRenderContext::updateSwapchain(const uint32_t imageCount) {
}

void VulkanRenderContext::updateSwapchain(const std::set<vk::ImageUsageFlagBits> &imageUsageFlags) {
}

void VulkanRenderContext::updateSwapchain(const vk::Extent2D &extent,
                                          const vk::SurfaceTransformFlagBitsKHR transform) {
}

bool VulkanRenderContext::hasSwapchain() {
    return swapchain != nullptr;
}

void VulkanRenderContext::recreate() {
    ELMT_CORE_TRACE("Recreated swapchain!");
    vk::Extent2D extent = swapchain->getswapChainExtent();
    auto frame = frames.begin();
    for (auto &image : swapchain->getSwapChainImages()) {
        auto swapchainImage = VulkanImage(device, image, extent, swapchain->getSwapChainImageFormat());
        auto renderTarget = VulkanRenderTarget::createRenderTarget(std::move(swapchainImage));
        if (frame != frames.end()) {
            (*frame)->updateRenderTarget(std::move(renderTarget));
        } else {
            frames.emplace_back(std::make_unique<VulkanRenderFrame>(device, std::move(renderTarget)));
        }
        ++frame;
    }
}

void VulkanRenderContext::recreateSwapchain() {
    device.getHandle().waitIdle();
    // Clear framebuffers
    device.clearFramebuffers();
    vk::Extent2D extent = swapchain->getswapChainExtent();
    auto frame = frames.begin();
    for (auto &image : swapchain->getSwapChainImages()) {
        auto swapchainImage = VulkanImage(device, image, extent, swapchain->getSwapChainImageFormat());
        auto renderTarget = VulkanRenderTarget::createRenderTarget(std::move(swapchainImage));
        (*frame)->updateRenderTarget(std::move(renderTarget));
        ++frame;
    }
}

VulkanCommandBuffer &VulkanRenderContext::begin() {
    acquiredSemaphore = beginFrame();
    if (!acquiredSemaphore) {
        ELMT_CORE_ERROR("Could not start frame.");
    }
    const auto queue = device.getGraphicsQueue();
    return getActiveFrame().getCommandBufer();
}

void VulkanRenderContext::submit(VulkanCommandBuffer &commandBuffer) {
    vk::Semaphore renderSemaphore
      = submit(queue, commandBuffer, acquiredSemaphore, vk::PipelineStageFlagBits::eColorAttachmentOutput);
    endFrame(renderSemaphore);
    acquiredSemaphore = nullptr;
}

vk::Semaphore VulkanRenderContext::beginFrame() {
    handleSurfaceChanges();
    auto &prevFrame = *frames.at(activeFrameIndex);
    auto acquiredSemaphore = prevFrame.requestSemaphore();
    auto fence = prevFrame.requestFence();
    auto result = swapchain->acquireNextImage(activeFrameIndex, acquiredSemaphore, fence);
    return acquiredSemaphore;
}

void VulkanRenderContext::submit(const VulkanQueue &queue, const VulkanCommandBuffer &commandBuffer) {
    VulkanRenderFrame &frame = getActiveFrame();
    vk::CommandBuffer cmdBuf = commandBuffer.getCommandBuffer();
    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuf;
    vk::Fence fence = frame.requestFence();
    queue.submit({ submitInfo }, fence);
}

vk::Semaphore VulkanRenderContext::submit(const VulkanQueue &queue,
                                          const VulkanCommandBuffer &commandBuffer,
                                          vk::Semaphore waitSemaphore,
                                          vk::PipelineStageFlags waitPipelineStage) {
    VulkanRenderFrame &frame = getActiveFrame();
    vk::Semaphore signalSemaphore = frame.requestSemaphore();
    vk::CommandBuffer cmdBuf = commandBuffer.getCommandBuffer();
    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuf;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &waitSemaphore;
    submitInfo.pWaitDstStageMask = &waitPipelineStage;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &signalSemaphore;
    vk::Fence fence = frame.requestFence();
    queue.submit({ submitInfo }, fence);
    return signalSemaphore;
}

void VulkanRenderContext::waitFrame() {
    getActiveFrame().reset();
}

void VulkanRenderContext::endFrame(vk::Semaphore semaphore) {
    vk::PresentInfoKHR presentInfo;
    presentInfo.setWaitSemaphoreCount(1);
    presentInfo.setPWaitSemaphores(&semaphore);
    vk::SwapchainKHR swapChains[] = { swapchain->getSwapChain() };
    presentInfo.setSwapchainCount(1);
    presentInfo.setPSwapchains(swapChains);
    presentInfo.setPImageIndices(&activeFrameIndex);

    vk::Result result = device.getPresentQueue().present(presentInfo);
    if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR) {
        handleSurfaceChanges();
    } else if (result != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to present swap chain image!");
    }
}

VulkanRenderFrame &VulkanRenderContext::getActiveFrame() {
    return *frames.at(activeFrameIndex);
}

uint32_t VulkanRenderContext::getActiveFrameIndex() {
    return activeFrameIndex;
}

VulkanRenderFrame &VulkanRenderContext::getLastRenderedFrame() {
    return *frames.at(activeFrameIndex);
}

vk::Semaphore VulkanRenderContext::requestSemaphore() {
    return getActiveFrame().requestSemaphore();
}

} // namespace Elements
