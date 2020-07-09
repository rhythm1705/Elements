#pragma once

#include "VulkanQueue.h"

namespace Elements {
class VulkanPresentQueue : public VulkanQueue {
  public:
    static VulkanPresentQueue *getInstance();

    void init(const QueueFamilyIndices &queueFamilyIndices);

  private:
    VulkanPresentQueue() = default;
    ~VulkanPresentQueue(){};

    static VulkanPresentQueue *vulkanPresentQueue;
};

} // namespace Elements