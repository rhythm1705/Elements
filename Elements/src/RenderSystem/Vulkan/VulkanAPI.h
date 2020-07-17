#pragma once

namespace Elements {

class VulkanInstance;
class VulkanValidationLayers;
class VulkanDevice;
class VulkanGraphicsQueue;
class VulkanPresentQueue;
class VulkanSwapchain;
class VulkanImageView;
class VulkanStandardRenderPass;
class VulkanGraphicsPipeline;
class VulkanFramebuffer;
class VulkanCommandPool;
class VulkanCommandBuffer;
class VulkanSyncObjects;

class VulkanAPI {
  public:
    VulkanAPI();
    ~VulkanAPI();

    void drawFrame();
    void recreateSwapChain();
    void cleanUpSwapchain();

  private:
    std::unique_ptr<VulkanInstance> instance;
    std::unique_ptr<VulkanDevice> device;
    std::unique_ptr<VulkanSwapchain> swapChain;

    vk::Queue graphicsQueue;
    vk::Queue presentQueue;
};
} // namespace Elements