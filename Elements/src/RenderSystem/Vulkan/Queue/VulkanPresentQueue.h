#pragma once

#include "VulkanQueue.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanPresentQueue : public VulkanQueue {
  public:
    VulkanPresentQueue *getInstance();

    void init(const QueueFamilyIndices &queueFamilyIndices);

  private:
    VulkanPresentQueue() = default;
    ~VulkanPresentQueue(){};

    static VulkanPresentQueue *vulkanPresentQueue;
};

} // namespace Elements