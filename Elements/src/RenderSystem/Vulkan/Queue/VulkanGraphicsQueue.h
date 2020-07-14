#pragma once

#include "VulkanQueue.h"

namespace Elements {

struct QueueFamilyIndices {};

class VulkanGraphicsQueue : public VulkanQueue {
  public:
    VulkanGraphicsQueue(vk::Device device, const QueueFamilyIndices &queueFamilyIndices);
    ~VulkanGraphicsQueue(){};
};

} // namespace Elements