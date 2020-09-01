#include "VulkanRenderPass.h"

#include "VulkanDevice.h"
#include "VulkanRenderTarget.h"

namespace Elements {

VulkanRenderPass::VulkanRenderPass(VulkanDevice &device,
                                   const std::vector<Attachment> &attachments,
                                   const std::vector<LoadStoreInfo> &loadStoreInfos,
                                   const std::vector<SubpassInfo> &subpasses) :
device{ device },
subpassCount{ std::max<size_t>(1, subpasses.size()) } {
    // Get all attachment descriptions
    std::vector<vk::AttachmentDescription> attachmentDescriptions;
    for (size_t i = 0U; i < attachments.size(); ++i) {
        vk::AttachmentDescription attachment;
        attachment.setFormat(attachments[i].format);
        attachment.setSamples(attachments[i].samples);
        attachment.setInitialLayout(attachments[i].initialLayout);
        attachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);
        if (i < loadStoreInfos.size()) {
            attachment.setLoadOp(loadStoreInfos[i].loadOp);
            attachment.setStoreOp(loadStoreInfos[i].storeOp);
            attachment.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare);
            attachment.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
        }
        attachmentDescriptions.push_back(std::move(attachment));
    }

    // Store attachments for every subpass
    std::vector<std::vector<vk::AttachmentReference>> inputAttachments{ subpassCount };
    std::vector<std::vector<vk::AttachmentReference>> colorAttachments{ subpassCount };
    std::vector<std::vector<vk::AttachmentReference>> depthStencilAttachments{ subpassCount };
    std::vector<std::vector<vk::AttachmentReference>> colorResolveAttachments{ subpassCount };
    std::vector<std::vector<vk::AttachmentReference>> depthResolveAttachments{ subpassCount };

    // Fill the attachments
    for (size_t i = 0; i < subpasses.size(); ++i) {
        auto &subpass = subpasses[i];
        // Fill color attachments
        vk::AttachmentReference colorAttachmentRef(0, vk::ImageLayout::eColorAttachmentOptimal);
        colorAttachments[i].push_back(colorAttachmentRef);
    }

    // Fill subpass descrtiptions
    std::vector<vk::SubpassDescription> subpassDescriptions;
    subpassDescriptions.reserve(subpassCount);
    for (size_t i = 0; i < subpasses.size(); ++i) {
        auto &subpass = subpasses[i];
        vk::SubpassDescription subpassDescription(vk::SubpassDescriptionFlags(),
                                                  vk::PipelineBindPoint::eGraphics,
                                                  0,
                                                  nullptr,
                                                  1,
                                                  colorAttachments[i].data());
        subpassDescriptions.push_back(subpassDescription);
    }

    // Create subpasss dependencies
    std::vector<vk::SubpassDependency> subpassDependencies(1);
    for (uint32_t i = 0; i < subpassDependencies.size(); ++i) {
        subpassDependencies[i].setSrcSubpass(VK_SUBPASS_EXTERNAL);
        subpassDependencies[i].setDstSubpass(0);
        subpassDependencies[i].setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        subpassDependencies[i].setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        subpassDependencies[i].setSrcAccessMask(vk::AccessFlagBits::eColorAttachmentRead);
        subpassDependencies[i].setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);
    }

    vk::RenderPassCreateInfo renderPassInfo(vk::RenderPassCreateFlags(),
                                            1,
                                            attachmentDescriptions.data(),
                                            1,
                                            subpassDescriptions.data(),
                                            1,
                                            subpassDependencies.data());
    if (device.getHandle().createRenderPass(&renderPassInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to create render pass!");
    }
}

VulkanRenderPass::~VulkanRenderPass() {
    if (handle) {
        device.getHandle().destroyRenderPass(handle);
    }
}

} // namespace Elements
