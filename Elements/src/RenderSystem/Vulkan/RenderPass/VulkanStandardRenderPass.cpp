#include "VulkanStandardRenderPass.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanStandardRenderPass *VulkanStandardRenderPass::instance = nullptr;

VulkanStandardRenderPass *VulkanStandardRenderPass::getInstance() {
    if (!instance) {
        instance = new VulkanStandardRenderPass();
    }
    return instance;
}

void VulkanStandardRenderPass::init(vk::Format &swapChainImageFormat) {
    vk::AttachmentDescription colorAttachment(
      vk::AttachmentDescriptionFlags(), swapChainImageFormat, vk::SampleCountFlagBits::e1,
      vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare,
      vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eUndefined, vk::ImageLayout::ePresentSrcKHR);

    vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

    vk::SubpassDescription subpass(
      vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, 1, &colorAttachmentRef);

    vk::SubpassDependency dependency;
    dependency.setSrcSubpass(VK_SUBPASS_EXTERNAL);
    dependency.setDstSubpass(0);
    dependency.setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
    dependency.setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
    dependency.setSrcAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);
    dependency.setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);

    vk::RenderPassCreateInfo renderPassInfo(
      vk::RenderPassCreateFlags(), 1, &colorAttachment, 1, &subpass, 1, &dependency);

    if (VulkanDevice::getInstance()->getVulkanDevice().createRenderPass(&renderPassInfo, nullptr, &renderPass)
        != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create render pass!");
    }
}

} // namespace Elements
