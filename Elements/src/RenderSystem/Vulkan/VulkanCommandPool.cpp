#include "VulkanCommandPool.h"

namespace Elements {

VulkanCommandPool::VulkanCommandPool(VulkanQueue::QueueFamilyIndices queueFamilyIndices) {
    vk::CommandPoolCreateInfo poolInfo(
      vk::CommandPoolCreateFlags(), queueFamilyIndices.graphicsFamily.value());
    if (VulkanDevice::getInstance()->getVulkanDevice().createCommandPool(&poolInfo, nullptr, &commandPool)
        != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create command pool!");
    }
}

VulkanCommandPool::~VulkanCommandPool() {
    VulkanDevice::getInstance()->getVulkanDevice().destroyCommandPool(commandPool);
}

} // namespace Elements
