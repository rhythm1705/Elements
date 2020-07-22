#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;

class VulkanImage {
  public:
    VulkanImage(VulkanDevice &device, vk::Image handle, const vk::Extent2D &extent, vk::Format format);
    ~VulkanImage();

    vk::Image getHandle() const { return handle; };

    VulkanDevice &getDevice() { return device; };
    vk::Format getFormat() const { return format; };

  private:
    vk::Image handle;

    VulkanDevice &device;

    vk::Extent2D extent;
    vk::Format format;
    //vk::ImageUsageFlags imageUsage;
};

} // namespace Elements
