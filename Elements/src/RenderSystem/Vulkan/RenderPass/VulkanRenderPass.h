#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanRenderPass {
  public:
    vk::RenderPass &getRenderPass() { return renderPass; }

    void destroy();

  protected:
    VulkanRenderPass() = default;
    ~VulkanRenderPass(){};

    vk::RenderPass renderPass;
};

} // namespace Elements
