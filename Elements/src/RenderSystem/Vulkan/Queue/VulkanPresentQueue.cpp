#include "VulkanPresentQueue.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanPresentQueue *VulkanPresentQueue::vulkanPresentQueue = nullptr;

VulkanPresentQueue *VulkanPresentQueue::getInstance() {
    if (!vulkanPresentQueue) {
        vulkanPresentQueue = new VulkanPresentQueue();
    }
    return vulkanPresentQueue;
}
void VulkanPresentQueue::init(const QueueFamilyIndices &queueFamilyIndices) {
    VulkanDevice::getInstance()->getVulkanDevice().getQueue(queueFamilyIndices.presentFamily.value(), 0, &queue);
}
} // namespace Elements