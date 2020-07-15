#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanRenderFrame;

class VulkanCommandPool {
  public:
    VulkanCommandPool(VulkanDevice &device,
                      QueueFamilyIndices queueFamilyIndices,
                      VulkanRenderFrame *renderFrame = nullptr);
    ~VulkanCommandPool();

    vk::CommandPool getHandle() { return handle; }

  private:
    VulkanDevice &device;

    vk::CommandPool handle;

    VulkanRenderFrame *renderFrame;
};

} // namespace Elements
