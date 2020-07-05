#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanQueue {
  public:
    vk::Queue &getQueue() { return queue; };

    struct QueueFamilyIndices {
        int graphics_family = -1;
        int present_family = -1;

        bool is_complete() const { return graphics_family >= 0 && present_family >= 0; }
    };

  protected:
    vk::Queue queue;
};

} // namespace Elements
