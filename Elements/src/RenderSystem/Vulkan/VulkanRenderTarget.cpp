#include "VulkanRenderTarget.h"

#include "VulkanImage.h"
#include "VulkanImageView.h"

namespace Elements {

Attachment::Attachment(vk::Format format, vk::SampleCountFlagBits samples, vk::ImageUsageFlags usage)
: format{ format }, samples{ samples }, usage{ usage } {}

const std::unique_ptr<VulkanRenderTarget> VulkanRenderTarget::createRenderTarget(VulkanImage &&image) {
    std::vector<VulkanImage> images;
    images.push_back(std::move(image));
    return std::make_unique<VulkanRenderTarget>(std::move(images));
}

VulkanRenderTarget::VulkanRenderTarget(std::vector<VulkanImage> &&images)
: device{ images.back().getDevice() }, images{ std::move(images) } {
    for (auto &image : this->images) {
        /*if (image.get() != VK_IMAGE_TYPE_2D) {
            throw VulkanException{ VK_ERROR_INITIALIZATION_FAILED, "Image type is not 2D" };
        }*/
        imageViews.emplace_back(image, vk::ImageViewType::e2D);
        // attachments.emplace_back(Attachment{ image.getFormat(), image.get_sample_count(),
        // image.get_usage() });
    }
}

} // namespace Elements
