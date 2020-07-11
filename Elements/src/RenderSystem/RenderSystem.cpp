#include "RenderSystem.h"

#include "Core/Application.h"
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

void RenderSystem::startUp() {
    auto window = Application::get().getWindow().getWindowPtr();
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        data.framebufferResized = true;
    });
    init();
}

void RenderSystem::shutDown() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    device.waitIdle();
    cleanUpSwapchain();

    for (size_t i = 0; i < 2; i++) {
        device.destroySemaphore(renderFinishedSemaphores[i]);
        device.destroySemaphore(imageAvailableSemaphores[i]);
        device.destroyFence(inFlightFences[i]);
    }

    device.destroyCommandPool(commandPool);
    device.destroy();

    if (enableValidationLayers) {
        VulkanValidationLayers::destroyDebugMessenger();
    }
    auto instance = VulkanInstance::getInstance()->getVulkanInstance();
    auto surface = VulkanSurface::getInstance()->getVulkanSurface();
    instance.destroySurfaceKHR(surface);
    instance.destroy();
}

void RenderSystem::onUpdate() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    device.waitForFences(1, &inFlightFences[currentFrame], true, std::numeric_limits<uint64_t>::max());
    uint32_t imageIndex;

    vk::Result result = device.acquireNextImageKHR(swapChain, std::numeric_limits<uint64_t>::max(),
                                                   imageAvailableSemaphores[currentFrame], nullptr, &imageIndex);
    if (result == vk::Result::eErrorOutOfDateKHR) {
        recreateSwapChain();
        return;
    } else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
        ELMT_CORE_ERROR("failed to acquire swap chain image!");
    }
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

    result = presentQueue.presentKHR(&presentInfo);
    if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR
        || Application::get().getWindow().isFramebufferResized()) {
        Application::get().getWindow().setFramebufferResisze(false);
        recreateSwapChain();
    } else if (result != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % 2;
}

void RenderSystem::recreateSwapChain() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    auto window = Application::get().getWindow().getWindowPtr();
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }
    device.waitIdle();
    cleanUpSwapchain();

    auto swapchainObj = new VulkanSwapChain();
    swapChain = swapchainObj->getSwapChain();
    ELMT_CORE_TRACE("Initialized vulkan swap chain.");

    auto imageViewsObj = new VulkanImageViews(swapchainObj);
    swapChainImageViews = imageViewsObj->getSwapChainImageViews();
    ELMT_CORE_TRACE("Initialized vulkan image views.");

    auto &imageFormat = swapchainObj->getSwapChainImageFormat();
    auto &extent = swapchainObj->getswapChainExtent();

    auto renderPass = VulkanStandardRenderPass::getInstance();
    renderPass->init(imageFormat);
    ELMT_CORE_TRACE("Initialized vulkan render pass.");

    auto pipeline = new VulkanGraphicsPipeline("assets/shaders/vert.spv", "assets/shaders/frag.spv", extent);
    graphicsPipeline = pipeline->getPipeline();
    pipelineLayout = pipeline->getPipelineLayout();
    ELMT_CORE_TRACE("Initialized vulkan graphics pipeline.");

    auto framebuffersObj = new VulkanFramebuffers(imageViewsObj, extent);
    framebuffers = framebuffersObj->getFrameBuffers();
    ELMT_CORE_TRACE("Initialized vulkan framebuffers.");

    auto commandBuffersObj = new VulkanCommandBuffers(commandPool, framebuffers, extent, graphicsPipeline);
    commandBuffers = commandBuffersObj->getCommandBuffers();
}

void RenderSystem::cleanUpSwapchain() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    for (auto framebuffer : framebuffers) {
        device.destroyFramebuffer(framebuffer);
    }

    device.freeCommandBuffers(
      commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
    commandBuffers.clear();

    device.destroyPipeline(graphicsPipeline);
    device.destroyPipelineLayout(pipelineLayout);
    device.destroyRenderPass(VulkanStandardRenderPass::getInstance()->getRenderPass());

    for (auto imageView : swapChainImageViews) {
        device.destroyImageView(imageView);
    }

    device.destroySwapchainKHR(swapChain);
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

    auto imageViewsObj = new VulkanImageViews(swapchainObj);
    swapChainImageViews = imageViewsObj->getSwapChainImageViews();
    ELMT_CORE_TRACE("Initialized vulkan image views.");

    auto &imageFormat = swapchainObj->getSwapChainImageFormat();
    auto &extent = swapchainObj->getswapChainExtent();

    auto renderPass = VulkanStandardRenderPass::getInstance();
    renderPass->init(imageFormat);
    ELMT_CORE_TRACE("Initialized vulkan render pass.");

    auto pipeline = new VulkanGraphicsPipeline("assets/shaders/vert.spv", "assets/shaders/frag.spv", extent);
    graphicsPipeline = pipeline->getPipeline();
    pipelineLayout = pipeline->getPipelineLayout();

    auto framebuffersObj = new VulkanFramebuffers(imageViewsObj, extent);
    framebuffers = framebuffersObj->getFrameBuffers();

    auto commandPoolObj
      = new VulkanCommandPool(device->findQueueFamilies(device->getVulkanPhysicalDevice()));
    commandPool = commandPoolObj->getCommandPool();
    auto commandBuffersObj = new VulkanCommandBuffers(commandPool, framebuffers, extent, graphicsPipeline);
    commandBuffers = commandBuffersObj->getCommandBuffers();

    auto syncObject = new VulkanSyncObjects(swapchainObj->getSwapChainImages().size());
    imageAvailableSemaphores = syncObject->getImageAvailableSemaphores();
    renderFinishedSemaphores = syncObject->getRenderFinishedSemaphores();
    inFlightFences = syncObject->getInFlightFences();
    imagesInFlight = syncObject->getImagesInFlightFences();
    ELMT_CORE_TRACE("Initialized vulkan complete.");
}

} // namespace Elements
