#include "VulkanFrameBuffer.h"

#include "VulkanDevice.h"
#include "VulkanImageView.h"
#include "VulkanRenderPass.h"
#include "VulkanRenderTarget.h"

namespace Elements {

VulkanFramebuffer::VulkanFramebuffer(VulkanDevice &device, const VulkanRenderTarget &renderTarget, const VulkanRenderPass &renderPass) :
device{ device }, extent{ renderTarget.getExtent() } {
    std::vector<vk::ImageView> attachments;
    for (auto &view : renderTarget.getImageViews()) {
        attachments.emplace_back(view.getHandle());
    }
    vk::FramebufferCreateInfo createInfo;
    createInfo.setRenderPass(renderPass.getHandle());
    createInfo.setAttachmentCount(attachments.size());
    createInfo.setPAttachments(attachments.data());
    createInfo.setWidth(extent.width);
    createInfo.setHeight(extent.height);
    createInfo.setLayers(1);
    if (device.getHandle().createFramebuffer(&createInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Cannot create Framebuffer");
    }
}

VulkanFramebuffer::~VulkanFramebuffer() {
    if (handle) {
        device.getHandle().destroyFramebuffer(handle, nullptr);
    }
}

} // namespace Elements
