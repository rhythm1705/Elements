#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanCommandBuffers {
  public:
    VulkanCommandBuffers(vk::CommandPool commandPool,
                         std::vector<vk::Framebuffer> framebuffers,
                         vk::Extent2D swapChainExtent,
                         vk::Pipeline pipeline);
    ~VulkanCommandBuffers();

    std::vector<vk::CommandBuffer> getCommandBuffers() { return commandBuffers; };

  private:
    std::vector<vk::CommandBuffer> commandBuffers;
};

} // namespace Elements
