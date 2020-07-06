#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanQueue {
  public:
    vk::Queue &getQueue() { return queue; };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };

  protected:
    vk::Queue queue;
};

} // namespace Elements
