#pragma once
#include "RenderSystem/Vulkan/RenderPass/VulkanRenderPass.h"

namespace Elements {
class VulkanStandardRenderPass : public VulkanRenderPass {
  public:
    static VulkanStandardRenderPass *getInstance();

    void init(vk::Format &swapChainImageFormat);

  private:
    VulkanStandardRenderPass() = default;
    ~VulkanStandardRenderPass(){};

    static VulkanStandardRenderPass *instance;
};

} // namespace Elements
