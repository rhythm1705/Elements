#pragma once
#include "RenderSystem/Vulkan/RenderPass/VulkanRenderPass.h"

namespace Elements {

class VulkanGUIRenderPass : public VulkanRenderPass {
  public:
    static VulkanGUIRenderPass *getInstance();

    void init(vk::Format &swapChainImageFormat);

  private:
    VulkanGUIRenderPass();
    ~VulkanGUIRenderPass(){};

    static VulkanGUIRenderPass *instance;
};
} // namespace Elements
