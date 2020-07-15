#include "VulkanAPI.h"

#include "Queue/VulkanGraphicsQueue.h"
#include "Queue/VulkanPresentQueue.h"
#include "RenderPass/VulkanGUIRenderPass.h"
#include "RenderPass/VulkanStandardRenderPass.h"
#include "VulkanCommandBuffers.h"
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanFrameBuffers.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanImageView.h"
#include "VulkanInstance.h"
#include "VulkanShaderManager.h"
#include "VulkanSwapChain.h"
#include "VulkanSyncObjects.h"
#include "VulkanValidationLayers.h"

namespace Elements {

VulkanAPI::VulkanAPI() {
    instance = std::make_unique<VulkanInstance>("Elements Game Engine", 1, "Elements", 1);
    ELMT_CORE_TRACE("Initialized vulkan instance.");

    if (enableValidationLayers) {
        VulkanValidationLayers::setupDebugMessenger();
    }

    device = std::make_unique<VulkanDevice>(instance->getHandle(), instance->getSurface());
    ELMT_CORE_TRACE("Initialized vulkan device.");

    graphicsQueue = VulkanGraphicsQueue(device->getHandle(), device->getQueueFamilyIndices()).getHandle();
    ELMT_CORE_TRACE("Initialized vulkan graphics queue.");

    presentQueue = VulkanPresentQueue(device->getHandle(), device->getQueueFamilyIndices()).getHandle();
    ELMT_CORE_TRACE("Initialized vulkan present queue.");

    swapChain = std::make_unique<VulkanSwapchain>(device->getHandle(), instance->getSurface());
    ELMT_CORE_TRACE("Initialized vulkan swap chain.");

    auto imageViewsObj = new VulkanImageView(swapchainObj);
    swapChainImageViews = imageViewsObj->getHandle();
    ELMT_CORE_TRACE("Initialized vulkan image views.");

    auto &imageFormat = swapchainObj->getSwapChainImageFormat();
    auto &extent = swapchainObj->getswapChainExtent();

    auto renderPass = VulkanStandardRenderPass::getInstance();
    renderPass->init(imageFormat);
    ELMT_CORE_TRACE("Initialized vulkan render pass.");

    auto pipeline = new VulkanGraphicsPipeline("assets/shaders/vert.spv", "assets/shaders/frag.spv", extent);
    graphicsPipeline = pipeline->getPipeline();
    pipelineLayout = pipeline->getPipelineLayout();

    auto framebuffersObj = new VulkanFramebuffer(imageViewsObj, extent);
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

VulkanAPI::~VulkanAPI() {}

void VulkanAPI::drawFrame() {}

void VulkanAPI::recreateSwapChain() {}

void VulkanAPI::cleanUpSwapchain() {}

} // namespace Elements
