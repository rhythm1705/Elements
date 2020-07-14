#include "VulkanGraphicsQueue.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {

VulkanGraphicsQueue::VulkanGraphicsQueue(vk::Device device, const QueueFamilyIndices &queueFamilyIndices) {
    device.getQueue(queueFamilyIndices.graphicsFamily.value(), 0, &handle);
}
} // namespace Elements