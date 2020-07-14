#pragma once

#include "RenderSystem/Vulkan/VulkanSwapChain.h"

#include <vulkan/vulkan.hpp>


namespace Elements {

class VulkanDevice;
class VulkanImage;

class VulkanImageView {
  public:
    VulkanImageView(VulkanImage &image, vk::ImageViewType viewType, vk::Format format = vk::Format::eUndefined);
    ~VulkanImageView();

    vk::ImageView getHandle() const { return handle; }

    void setImage(VulkanImage &image);

  private:
    vk::ImageView handle;

    VulkanDevice &device;

    VulkanImage *image{};
    vk::Format format;
};

} // namespace Elements
