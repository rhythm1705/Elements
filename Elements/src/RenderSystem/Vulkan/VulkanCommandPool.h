#pragma once

#include "VulkanDevice.h"


#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanRenderFrame;
class VulkanCommandBuffer;

class VulkanCommandPool {
  public:
    VulkanCommandPool(VulkanDevice &device,
                      QueueFamilyIndices queueFamilyIndices,
                      VulkanRenderFrame *renderFrame = nullptr);
    ~VulkanCommandPool();

    vk::CommandPool getHandle() {
        return handle;
    }

    VulkanDevice &getDevice() {
        return device;
    }

    VulkanCommandBuffer &getCommandBuffer();

  private:
    VulkanDevice &device;

    vk::CommandPool handle;

    std::vector<std::unique_ptr<VulkanCommandBuffer>> commandBuffers;
    uint32_t bufferCount{ 0 };

    VulkanRenderFrame *renderFrame;
};

} // namespace Elements
