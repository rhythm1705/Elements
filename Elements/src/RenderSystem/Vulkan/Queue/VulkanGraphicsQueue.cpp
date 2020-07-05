#include "VulkanGraphicsQueue.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanGraphicsQueue *vulkanGraphicsQueue = nullptr;

VulkanGraphicsQueue *VulkanGraphicsQueue::getInstance() {
    if (!vulkanGraphicsQueue) {
        vulkanGraphicsQueue = new VulkanGraphicsQueue();
    }
    return vulkanGraphicsQueue;
}
void VulkanGraphicsQueue::init() { VulkanDevice::getInstance()->getVulkanDevice() }
} // namespace Elements