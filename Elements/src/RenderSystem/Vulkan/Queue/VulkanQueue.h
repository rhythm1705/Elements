#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanQueue {
  public:
    vk::Queue &getHandle() { return handle; };

  protected:
    vk::Queue handle;
};

} // namespace Elements
