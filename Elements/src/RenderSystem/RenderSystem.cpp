#include "RenderSystem.h"

#include "Vulkan/Queue/VulkanGraphicsQueue.h"
#include "Vulkan/Queue/VulkanPresentQueue.h"
#include "Vulkan/RenderPass/VulkanStandardRenderPass.h"
#include "Vulkan/VulkanCommandBuffers.h"
#include "Vulkan/VulkanCommandPool.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanFrameBuffers.h"
#include "Vulkan/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanImageView.h"
#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanShaderManager.h"
#include "Vulkan/VulkanSurface.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanSyncObjects.h"
#include "Vulkan/VulkanValidationLayers.h"

namespace Elements {

void RenderSystem::startUp() { init(); }

void RenderSystem::shutDown() { VulkanDevice::getInstance()->getVulkanDevice().waitIdle(); }

void RenderSystem::onUpdate() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    device.waitForFences(1, &inFlightFences[currentFrame], true, std::numeric_limits<uint64_t>::max());
    uint32_t imageIndex;
    device.acquireNextImageKHR(swapChain, std::numeric_limits<uint64_t>::max(),
                               imageAvailableSemaphores[currentFrame], nullptr, &imageIndex);
    if (imagesInFlight[imageIndex]) {
        device.waitForFences(1, &imagesInFlight[imageIndex], VK_TRUE, std::numeric_limits<uint64_t>::max());
    }
    imagesInFlight[imageIndex] = inFlightFences[currentFrame];
    vk::Semaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
    vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
    vk::Semaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
    vk::SubmitInfo submitInfo(1, waitSemaphores, waitStages, 1, &commandBuffers[imageIndex], 1, signalSemaphores);

    device.resetFences(1, &inFlightFences[currentFrame]);

    if (graphicsQueue.submit(1, &submitInfo, inFlightFences[currentFrame]) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to submit draw command buffer!");
    }
    vk::PresentInfoKHR presentInfo;
    presentInfo.setWaitSemaphoreCount(1);
    presentInfo.setPWaitSemaphores(signalSemaphores);
    vk::SwapchainKHR swapChains[] = { swapChain };
    presentInfo.setSwapchainCount(1);
    presentInfo.setPSwapchains(swapChains);
    presentInfo.setPImageIndices(&imageIndex);

    presentQueue.presentKHR(&presentInfo);

    currentFrame = (currentFrame + 1) % 2;
}

void RenderSystem::init() {
    auto instance = VulkanInstance::getInstance();
    instance->init("Elements Game Engine", 1, "Elements", 1);
    ELMT_CORE_TRACE("Initialized vulkan instance.");

    if (enableValidationLayers) {
        VulkanValidationLayers::setupDebugMessenger();
    }

    auto surface = VulkanSurface::getInstance();
    surface->init();
    ELMT_CORE_TRACE("Initialized vulkan surface.");

    auto device = VulkanDevice::getInstance();
    device->init();
    ELMT_CORE_TRACE("Initialized vulkan device.");

    auto graphicsQueueObj = VulkanGraphicsQueue::getInstance();
    graphicsQueueObj->init(device->findQueueFamilies(device->getVulkanPhysicalDevice()));
    graphicsQueue = graphicsQueueObj->getQueue();
    ELMT_CORE_TRACE("Initialized vulkan graphics queue.");

    auto presentQueueObj = VulkanPresentQueue::getInstance();
    presentQueueObj->init(device->findQueueFamilies(device->getVulkanPhysicalDevice()));
    presentQueue = presentQueueObj->getQueue();
    ELMT_CORE_TRACE("Initialized vulkan present queue.");

    auto swapchainObj = new VulkanSwapChain();
    swapChain = swapchainObj->getSwapChain();
    ELMT_CORE_TRACE("Initialized vulkan swap chain.");

    auto imageViews = new VulkanImageViews(swapchainObj);
    ELMT_CORE_TRACE("Initialized vulkan image views.");

    auto &imageFormat = swapchainObj->getSwapChainImageFormat();
    auto &extent = swapchainObj->getswapChainExtent();

    auto renderPass = VulkanStandardRenderPass::getInstance();
    renderPass->init(imageFormat);
    ELMT_CORE_TRACE("Initialized vulkan render pass.");

    auto pipeline = new VulkanGraphicsPipeline("assets/shaders/vert.spv", "assets/shaders/frag.spv", extent);

    auto framebuffers = new VulkanFramebuffers(imageViews, extent);

    auto commandPool = new VulkanCommandPool(device->findQueueFamilies(device->getVulkanPhysicalDevice()));
    auto commandBuffersObj = new VulkanCommandBuffers(
      commandPool->getCommandPool(), framebuffers->getFrameBuffers(), extent, pipeline->getPipeline());
    commandBuffers = commandBuffersObj->getCommandBuffers();

    auto syncObject = new VulkanSyncObjects(swapchainObj->getSwapChainImages().size());
    imageAvailableSemaphores = syncObject->getImageAvailableSemaphores();
    renderFinishedSemaphores = syncObject->getRenderFinishedSemaphores();
    inFlightFences = syncObject->getInFlightFences();
    imagesInFlight = syncObject->getImagesInFlightFences();
    ELMT_CORE_TRACE("Initialized vulkan complete.");
}
} // namespace Elements
