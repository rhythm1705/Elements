#include "VulkanCommandPool.h"

#include "VulkanDevice.h"
#include "VulkanRenderFrame.h"
#include "VulkanRenderTarget.h"

namespace Elements {

VulkanCommandPool::VulkanCommandPool(VulkanDevice &d, QueueFamilyIndices queueFamilyIndices, VulkanRenderFrame *renderFrame)
: device{ device }, renderFrame{ renderFrame } {
    vk::CommandPoolCreateInfo poolInfo(
      vk::CommandPoolCreateFlags(), queueFamilyIndices.graphicsFamily.value());
    if (device.getHandle().createCommandPool(&poolInfo, nullptr, &handle) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create command pool!");
    }
}

VulkanCommandPool::~VulkanCommandPool() { device.getHandle().destroyCommandPool(handle); }

} // namespace Elements
