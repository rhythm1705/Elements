#pragma once
#include "RenderSystem/Vulkan/RenderPass/VulkanRenderPass.h"

namespace Elements {
class VulkanStandardRenderPass : public VulkanRenderPass {
  public:
    static VulkanStandardRenderPass *getInstance();

    void init(vk::Format &swapChainImageFormat);

    void destroy();

  private:
    VulkanStandardRenderPass();
    ~VulkanStandardRenderPass(){};

    VulkanStandardRenderPass *instance;
};

} // namespace Elements
