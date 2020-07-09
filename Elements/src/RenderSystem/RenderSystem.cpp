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

namespace Elements {

void RenderSystem::startUp() { init(); }

void RenderSystem::shutDown() {}

void RenderSystem::onUpdate() {}

void RenderSystem::init() {
    auto instance = VulkanInstance::getInstance();
    instance->init("Elements Game Engine", 0.1, "Elements", 0.1);

    auto surface = VulkanSurface::getInstance();
    surface->init();

    auto device = VulkanDevice::getInstance();
    device->init();

    auto graphicsQueue = VulkanGraphicsQueue::getInstance();
    graphicsQueue->init(device->getQueueFamilyIndices());

    auto swapchain = new VulkanSwapChain();
    auto imageViews = new VulkanImageViews(swapchain);

    auto imageFormat = swapchain->getSwapChainImageFormat();
    auto extent = swapchain->getswapChainExtent();

    auto renderPass = VulkanStandardRenderPass::getInstance();
    renderPass->init(imageFormat);

    auto pipeline = new VulkanGraphicsPipeline("", "", extent);

    auto framebuffers = new VulkanFramebuffers(imageViews, extent);
    auto commandPool = new VulkanCommandPool(device->getQueueFamilyIndices());
    auto commandBuffers = new VulkanCommandBuffers(
      commandPool->getCommandPool(), framebuffers->getFrameBuffers(), extent, pipeline->getPipeline());
}
} // namespace Elements
