#include "VulkanImage.h"

namespace Elements {

VulkanImage::VulkanImage(VulkanDevice &device, vk::Image handle, const vk::Extent2D &extent, vk::Format format)
: device{ device }, extent{ extent }, handle{ handle }, format{ format } {}

VulkanImage::~VulkanImage() {
}

inline vk::Extent2D VulkanImage::getExtent() const {
    return extent;
}

} // namespace Elements
