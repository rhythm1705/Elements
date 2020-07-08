#include "VulkanFrameBuffers.h"

#include "RenderSystem/Vulkan/RenderPass/VulkanStandardRenderPass.h"
#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {

VulkanFramebuffers::VulkanFramebuffers(VulkanImageViews *vulkanImageViews, vk::Extent2D extent) {
    auto imageViews = vulkanImageViews->getSwapChainImageViews();
    framebuffers.resize(imageViews.size());
    for (size_t i = 0; i < imageViews.size(); i++) {
        vk::ImageView attachments[] = { imageViews[i] };
        vk::FramebufferCreateInfo framebufferInfo(
          vk::FramebufferCreateFlags(), VulkanStandardRenderPass::getInstance()->getRenderPass(), 1,
          attachments, extent.width, extent.height, 1);
        if (VulkanDevice::getInstance()->getVulkanDevice().createFramebuffer(
              &framebufferInfo, nullptr, &framebuffers[i])
            != vk::Result::eSuccess) {
            ELMT_CORE_ERROR("Failed to create vulkan framebuffer!");
        }
    }
}

VulkanFramebuffers::~VulkanFramebuffers() {
    for (auto framebuffer : framebuffers) {
        VulkanDevice::getInstance()->getVulkanDevice().destroyFramebuffer(framebuffer);
    }
}

} // namespace Elements
