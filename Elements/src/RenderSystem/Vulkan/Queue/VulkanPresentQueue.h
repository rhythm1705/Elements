#pragma once

#include "VulkanQueue.h"

namespace Elements {

struct QueueFamilyIndices {};

class VulkanPresentQueue : public VulkanQueue {
  public:
    VulkanPresentQueue(vk::Device device, const QueueFamilyIndices &queueFamilyIndices);
    ~VulkanPresentQueue(){};
};

} // namespace Elements