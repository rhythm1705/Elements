#include "VulkanRenderContext.h"

#include "VulkanCommandBuffers.h"
#include "VulkanDevice.h"
#include "VulkanImage.h"
#include "VulkanQueue.h"
#include "VulkanRenderFrame.h"
#include "VulkanRenderTarget.h"
#include "VulkanSwapChain.h"

namespace Elements {
VulkanRenderContext::VulkanRenderContext(VulkanDevice &device, vk::SurfaceKHR surface, uint32_t width, uint32_t height) :
device{ device }, surfaceExtent{ width, height }, queue{ device.getGraphicsQueue() } {
    if (surface != VK_NULL_HANDLE) {
        swapchain = std::make_unique<VulkanSwapchain>(device, surface);
    }
}

VulkanRenderContext::~VulkanRenderContext() {
}

VulkanDevice &VulkanRenderContext::getDevice() {
    return device;
}

vk::Format VulkanRenderContext::getFormat() {
    return vk::Format();
}

VulkanSwapchain &VulkanRenderContext::getSwapchain() {
    return *swapchain;
}

vk::Extent2D VulkanRenderContext::getSurfaceExtent() const {
    return vk::Extent2D();
}

uint32_t VulkanRenderContext::getActiveFrameIndex() const {
    return uint32_t();
}

std::vector<std::unique_ptr<VulkanRenderFrame>> &VulkanRenderContext::getRenderFrames() {
    // TODO: insert return statement here
}

void VulkanRenderContext::handleSurfaceChanges() {
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
    if (acquiredSemaphore == VK_NULL_HANDLE) {
        ELMT_CORE_ERROR("Could not start frame.");
    }
    const auto queue = device.getGraphicsQueue();
    return getActiveFrame().getCommandBufer();
}

void VulkanRenderContext::submit(VulkanCommandBuffer &commandBuffer) {
}

vk::Semaphore VulkanRenderContext::beginFrame() {
    return vk::Semaphore();
}

vk::Semaphore VulkanRenderContext::submit(const VulkanQueue &queue,
                                          const VulkanCommandBuffer &commandBuffer,
                                          vk::Semaphore waitSemaphore,
                                          vk::PipelineStageFlags wait_pipelineStage) {
    return vk::Semaphore();
}

void VulkanRenderContext::submit(const VulkanQueue &queue, const VulkanCommandBuffer &commandBuffer) {
}

void VulkanRenderContext::waitFrame() {
}

void VulkanRenderContext::endFrame(vk::Semaphore semaphore) {
}

VulkanRenderFrame &VulkanRenderContext::getActiveFrame() {
    // TODO: insert return statement here
}

uint32_t VulkanRenderContext::getActiveFrameIndex() {
    return uint32_t();
}

VulkanRenderFrame &VulkanRenderContext::getLastRenderedFrame() {
    // TODO: insert return statement here
}

vk::Semaphore VulkanRenderContext::requestSemaphore() {
    return vk::Semaphore();
}

} // namespace Elements
