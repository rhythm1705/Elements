#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;

class VulkanSemaphorePool {
  public:
    VulkanSemaphorePool(VulkanDevice &device);
    ~VulkanSemaphorePool();

    vk::Semaphore requestSemaphore();
    uint32_t getActiveSemaphoreCount() const;
    void reset();

  private:
    VulkanDevice &device;

    std::vector<vk::Semaphore> semaphores;

    uint32_t activeSemaphoreCount{ 0 };
};

} // namespace Elements
