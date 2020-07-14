#include "VulkanImageView.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"
#include "VulkanImage.h"

namespace Elements {

VulkanImageView::VulkanImageView(VulkanImage &img, vk::ImageViewType viewType, vk::Format format)
: device{ img.getDevice() }, image{ &img }, format{ format } {
    if (format == vk::Format::eUndefined) {
        this->format = format = image->getFormat();
    }

    vk::ImageViewCreateInfo createInfo(
      vk::ImageViewCreateFlags(), image->getHandle(), vk::ImageViewType::e2D, format,
      vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG,
                           vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA),
      vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
    if (device.getHandle().createImageView(&createInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create vulkan swapchain image view!");
    }
}

VulkanImageView::~VulkanImageView() {
    if (handle != VK_NULL_HANDLE) {
        device.getHandle().destroyImageView(handle);
    }
}

void VulkanImageView::setImage(VulkanImage &img) { image = &img; }

} // namespace Elements