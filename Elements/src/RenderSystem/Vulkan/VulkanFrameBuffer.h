#pragma once

#include "RenderSystem/Vulkan/VulkanImageView.h"

namespace Elements {

class VulkanDevice;
class VulkanRenderTarget;
class VulkanRenderPass;

class VulkanFramebuffer {
  public:
    VulkanFramebuffer(VulkanDevice &device, const VulkanRenderTarget &renderTarget, const VulkanRenderPass &renderPass);
    ~VulkanFramebuffer();

    vk::Framebuffer getHandle() { return handle; }
    vk::Extent2D getExtent() { return extent; }

  private:
    VulkanDevice &device;

    vk::Framebuffer handle;
    vk::Extent2D extent;
};
} // namespace Elements
