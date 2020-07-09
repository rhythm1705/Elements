#include "VulkanGUIRenderPass.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanGUIRenderPass *VulkanGUIRenderPass::instance = nullptr;

VulkanGUIRenderPass *VulkanGUIRenderPass::getInstance() {
    if (!instance) {
        instance = new VulkanGUIRenderPass();
    }
    return instance;
}

void VulkanGUIRenderPass::init(vk::Format &swapChainImageFormat) {
    vk::AttachmentDescription colorAttachment(
      vk::AttachmentDescriptionFlags(), swapChainImageFormat, vk::SampleCountFlagBits::e1,
      vk::AttachmentLoadOp::eLoad, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eDontCare,
      vk::AttachmentStoreOp::eDontCare, vk::ImageLayout::eColorAttachmentOptimal,
      vk::ImageLayout::ePresentSrcKHR);

    vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);

    vk::SubpassDescription subpass(
      vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, 1, &colorAttachmentRef);

    vk::SubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

    vk::RenderPassCreateInfo renderPassInfo(
      vk::RenderPassCreateFlags(), 1, &colorAttachment, 1, &subpass, 1, &dependency);

    if (VulkanDevice::getInstance()->getVulkanDevice().createRenderPass(&renderPassInfo, nullptr, &renderPass)
        != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create render pass!");
    }
}

} // namespace Elements
