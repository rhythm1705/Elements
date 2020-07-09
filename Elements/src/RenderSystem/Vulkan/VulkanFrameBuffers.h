#pragma once

#include "RenderSystem/Vulkan/VulkanImageView.h"

namespace Elements {

class VulkanFramebuffers {
  public:
    VulkanFramebuffers(VulkanImageViews *vulkanImageViews, vk::Extent2D extent);
    ~VulkanFramebuffers();

    std::vector<vk::Framebuffer> getFrameBuffers() { return framebuffers; }

  private:
    std::vector<vk::Framebuffer> framebuffers;
};
} // namespace Elements
