#pragma once

#include "VulkanQueue.h"

namespace Elements {
class VulkanGraphicsQueue : public VulkanQueue {
  public:
    static VulkanGraphicsQueue *getInstance();

    void init(const QueueFamilyIndices &queueFamilyIndices);

  private:
    VulkanGraphicsQueue() = default;
    ~VulkanGraphicsQueue(){};

    static VulkanGraphicsQueue *vulkanGraphicsQueue;
};

} // namespace Elements