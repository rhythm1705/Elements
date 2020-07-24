#pragma once

#include "VulkanFencePool.h"
#include "VulkanSemaphorePool.h"

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanRenderTarget;
class VulkanCommandPool;
class VulkanCommandBuffer;

class VulkanRenderFrame {
  public:
    VulkanRenderFrame(VulkanDevice &device, std::unique_ptr<VulkanRenderTarget> &&renderTarget);
    ~VulkanRenderFrame();

    VulkanDevice &getDevice();

    void reset();

    const VulkanSemaphorePool &getSemaphorePool() const;
    const VulkanFencePool &getFencePool() const;
    const VulkanRenderTarget &getRenderTarget() const;

    void updateRenderTarget(std::unique_ptr<VulkanRenderTarget> &&renderTarget);

    VulkanCommandBuffer &getCommandBufer();

    vk::Fence requestFence();
    vk::Semaphore requestSemaphore();

  private:
    VulkanDevice &device;

    std::unique_ptr<VulkanCommandPool> commandPool;
    VulkanFencePool fencePool;
    VulkanSemaphorePool semaphorePool;

    std::unique_ptr<VulkanRenderTarget> renderTarget;
};

} // namespace Elements
