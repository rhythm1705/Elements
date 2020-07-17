#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;

class VulkanFencePool {
  public:
    VulkanFencePool(VulkanDevice &device);
    ~VulkanFencePool();

    vk::Fence requestFence();
    vk::Result wait(uint32_t timeout = std::numeric_limits<uint32_t>::max()) const;
    vk::Result reset();

  private:
    VulkanDevice &device;

    std::vector<vk::Fence> fences;

    uint32_t activeFenceCount{ 0 };
};

} // namespace Elements
