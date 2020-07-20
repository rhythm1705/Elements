#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanCommandPool;
class VulkanRenderPass;
class VulkanRenderTarget;
class VulkanFramebuffer;
class VulkanGraphicsPipeline;

class VulkanCommandBuffer {
  public:
    VulkanCommandBuffer(VulkanCommandPool commandPool);
    ~VulkanCommandBuffer();

    const vk::CommandBuffer getCommandBuffer() const { return handle; };

    vk::Result begin();
    void end();
    void beginRenderPass(VulkanRenderPass renderPass,
                         VulkanFramebuffer framebuffer,
                         VulkanRenderTarget &renderTarget,
                         std::vector<vk::ClearValue> clearValues);
    void bindPipeline(VulkanGraphicsPipeline pipeline);
    void draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
    void endRenderPass();

    struct RenderPassBinding {
        const VulkanRenderPass *renderPass;
        const VulkanFramebuffer *framebuffer;
    };

  private:
    vk::CommandBuffer handle;

    VulkanCommandPool commandPool;
    RenderPassBinding renderPassBinding;
};

} // namespace Elements
