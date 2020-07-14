#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

struct Attachment;
class VulkanDevice;

struct LoadStoreInfo {
    vk::AttachmentLoadOp loadOp = vk::AttachmentLoadOp::eClear;
    vk::AttachmentStoreOp storeOp = vk::AttachmentStoreOp::eStore;
};

struct SubpassInfo {
    std::vector<uint32_t> inputAttachments;
    std::vector<uint32_t> outputAttachments;
};

class VulkanRenderPass {
  public:
    VulkanRenderPass(VulkanDevice &device,
                     const std::vector<Attachment> &attachments,
                     const std::vector<LoadStoreInfo> &loadStoreInfos,
                     const std::vector<SubpassInfo> &subpasses);
    ~VulkanRenderPass();

    vk::RenderPass getHanlde() const { return handle; }

  private:
    vk::RenderPass handle;

    VulkanDevice &device;

    size_t subpassCount;

    // Store attachments for every subpass
    std::vector<std::vector<VkAttachmentReference>> input_attachments;
    std::vector<std::vector<VkAttachmentReference>> color_attachments;
    std::vector<std::vector<VkAttachmentReference>> depth_stencil_attachments;
};

} // namespace Elements
