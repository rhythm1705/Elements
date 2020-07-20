#include "VulkanCommandBuffers.h"

#include "RenderSystem/Vulkan/Pipeline/VulkanGraphicsPipeline.h"
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanFrameBuffer.h"
#include "VulkanRenderPass.h"
#include "VulkanRenderTarget.h"

namespace Elements {

VulkanCommandBuffer::VulkanCommandBuffer(VulkanCommandPool commandPool) :
commandPool{ commandPool } {
    vk::CommandBufferAllocateInfo allocInfo(commandPool.getHandle(), vk::CommandBufferLevel::ePrimary, 1);
    if (commandPool.getDevice().getHandle().allocateCommandBuffers(&allocInfo, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to allocate command buffers!");
    }
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
    if (handle != VK_NULL_HANDLE) {
        commandPool.getDevice().getHandle().freeCommandBuffers(commandPool.getHandle(), 1, &handle);
    }
}

vk::Result VulkanCommandBuffer::begin() {
    vk::CommandBufferBeginInfo beginInfo({}, nullptr);
    return handle.begin(&beginInfo);
}

void VulkanCommandBuffer::end() {
    handle.end();
}

void VulkanCommandBuffer::beginRenderPass(VulkanRenderPass renderPass,
                                          VulkanFramebuffer framebuffer,
                                          VulkanRenderTarget &renderTarget,
                                          std::vector<vk::ClearValue> clearValues) {
    vk::Rect2D renderArea({ 0, 0 }, renderTarget.getExtent());
    vk::RenderPassBeginInfo renderPassInfo(renderPass.getHandle(),
                                           framebuffer.getHandle(),
                                           renderArea,
                                           1,
                                           clearValues.data());
    handle.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);
}

void VulkanCommandBuffer::bindPipeline(VulkanGraphicsPipeline pipeline) {
    handle.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getHandle());
}

void VulkanCommandBuffer::draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    handle.draw(vertexCount, instanceCount, firstVertex, firstInstance);
}

void VulkanCommandBuffer::endRenderPass() {
    handle.endRenderPass();
}

} // namespace Elements
