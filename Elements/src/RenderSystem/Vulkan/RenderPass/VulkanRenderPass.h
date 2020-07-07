#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanRenderPass {
  public:
    vk::RenderPass &getRenderPass() { return renderPass; }

  private:
    vk::RenderPass renderPass;
};

} // namespace Elements
