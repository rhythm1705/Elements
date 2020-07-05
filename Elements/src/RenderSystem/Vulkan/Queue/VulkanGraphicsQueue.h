#pragma once

#include "VulkanQueue.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanGraphicsQueue : public VulkanQueue {
  public:
    VulkanGraphicsQueue *getInstance();

  private:
    VulkanGraphicsQueue() = default;
    ~VulkanGraphicsQueue(){};

    void init();

    static VulkanGraphicsQueue *vulkanGraphicsQueue;
};

} // namespace Elements