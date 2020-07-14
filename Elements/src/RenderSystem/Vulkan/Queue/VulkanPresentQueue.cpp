#include "VulkanPresentQueue.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {

VulkanPresentQueue::VulkanPresentQueue(vk::Device device, const QueueFamilyIndices &queueFamilyIndices) {
    device.getQueue(queueFamilyIndices.presentFamily.value(), 0, &handle);
}
} // namespace Elements