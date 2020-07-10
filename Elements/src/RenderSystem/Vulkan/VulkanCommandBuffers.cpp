#include "VulkanCommandBuffers.h"

#include "RenderSystem/Vulkan/RenderPass/VulkanStandardRenderPass.h"
#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {

VulkanCommandBuffers::VulkanCommandBuffers(vk::CommandPool commandPool,
                                           std::vector<vk::Framebuffer> framebuffers,
                                           vk::Extent2D swapChainExtent,
                                           vk::Pipeline pipeline) {
    commandBuffers.resize(framebuffers.size());
    vk::CommandBufferAllocateInfo allocInfo(
      commandPool, vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffers.size());

    if (VulkanDevice::getInstance()->getVulkanDevice().allocateCommandBuffers(
          &allocInfo, commandBuffers.data())
        != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to allocate command buffers!");
    }

    for (size_t i = 0; i < commandBuffers.size(); i++) {
        vk::CommandBufferBeginInfo beginInfo({}, nullptr);
        if (commandBuffers[i].begin(&beginInfo) != vk::Result::eSuccess) {
            ELMT_CORE_ERROR("failed to begin recording command buffer!");
        }
        vk::ClearValue clearColor = vk::ClearColorValue(std::array<float, 4>{ 0.0f, 0.0f, 0.0f, 1.0f });
        vk::Rect2D renderArea({ 0, 0 }, swapChainExtent);
        vk::RenderPassBeginInfo renderPassInfo(VulkanStandardRenderPass::getInstance()->getRenderPass(),
                                               framebuffers[i], renderArea, 1, &clearColor);

        commandBuffers[i].beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);
        commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
        commandBuffers[i].draw(3, 1, 0, 0);
        commandBuffers[i].endRenderPass();
        commandBuffers[i].end();
    }
}

VulkanCommandBuffers::~VulkanCommandBuffers() {}
} // namespace Elements
