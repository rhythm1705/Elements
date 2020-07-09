#include "VulkanGraphicsQueue.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanGraphicsQueue *VulkanGraphicsQueue::vulkanGraphicsQueue = nullptr;

VulkanGraphicsQueue *VulkanGraphicsQueue::getInstance() {
    if (!vulkanGraphicsQueue) {
        vulkanGraphicsQueue = new VulkanGraphicsQueue();
    }
    return vulkanGraphicsQueue;
}
void VulkanGraphicsQueue::init(const QueueFamilyIndices &queueFamilyIndices) {
    VulkanDevice::getInstance()->getVulkanDevice().getQueue(queueFamilyIndices.graphicsFamily.value(), 0, &queue);
}
} // namespace Elements