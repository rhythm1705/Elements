#pragma once

#include "vulkan/vulkan.hpp"
#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
class VulkanCommandPool {
  public:
    VulkanCommandPool(VulkanQueue::QueueFamilyIndices queueFamilyIndices);
    ~VulkanCommandPool();

    vk::CommandPool getCommandPool() { return commandPool; }

  private:
    vk::CommandPool commandPool;
};

} // namespace Elements
