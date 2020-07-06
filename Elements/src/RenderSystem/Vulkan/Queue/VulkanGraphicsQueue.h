#pragma once

#include "VulkanQueue.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanGraphicsQueue : public VulkanQueue {
  public:
    VulkanGraphicsQueue *getInstance();

    void init(const QueueFamilyIndices &queueFamilyIndices);

  private:
    VulkanGraphicsQueue() = default;
    ~VulkanGraphicsQueue(){};

    static VulkanGraphicsQueue *vulkanGraphicsQueue;
};

} // namespace Elements