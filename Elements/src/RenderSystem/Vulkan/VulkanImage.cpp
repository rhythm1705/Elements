#include "VulkanImage.h"

namespace Elements {

VulkanImage::VulkanImage(VulkanDevice &device, vk::Image handle, const vk::Extent2D &extent, vk::Format format, vk::ImageUsageFlags usage)
: device{ device }, extent{ extent }, handle{ handle }, format{ format }, imageUsage{ usage } {}

VulkanImage::~VulkanImage() {}

} // namespace Elements
