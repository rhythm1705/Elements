#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanImage;
class VulkanImageView;

struct Attachment {
    vk::Format format{ vk::Format::eUndefined };
    vk::SampleCountFlagBits samples{ vk::SampleCountFlagBits::e1 };
    vk::ImageUsageFlags usage{ vk::ImageUsageFlagBits::eSampled };
    vk::ImageLayout initialLayout{ vk::ImageLayout::eUndefined };

    Attachment() = default;
    Attachment(vk::Format format, vk::SampleCountFlagBits samples, vk::ImageUsageFlags usage);
};

class VulkanRenderTarget {
  public:
    static const std::unique_ptr<VulkanRenderTarget> createRenderTarget(VulkanImage &&image);

    VulkanRenderTarget(std::vector<VulkanImage> &&images);
    //~VulkanRenderTarget();

    const vk::Extent2D &getExtent() const { return extent; };
    const std::vector<VulkanImageView> &getImageViews() const { return imageViews; };
    const std::vector<Attachment> &getAttachments() const { return attachments; };

  private:
    VulkanDevice &device;

    vk::Extent2D extent;
    std::vector<VulkanImage> images;
    std::vector<VulkanImageView> imageViews;
    std::vector<Attachment> attachments;
};

} // namespace Elements
