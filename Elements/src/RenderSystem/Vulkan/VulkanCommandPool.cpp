#include "VulkanCommandPool.h"

#include "VulkanCommandBuffers.h"
#include "VulkanRenderFrame.h"
#include "VulkanRenderTarget.h"

namespace Elements {

VulkanCommandPool::VulkanCommandPool(VulkanDevice &device, QueueFamilyIndices queueFamilyIndices, VulkanRenderFrame *renderFrame) :
device{ device }, renderFrame{ renderFrame } {
    vk::CommandPoolCreateInfo poolInfo(vk::CommandPoolCreateFlags(),
                                       queueFamilyIndices.graphicsFamily.value());
    if (device.getHandle().createCommandPool(&poolInfo, nullptr, &handle) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create command pool!");
    }
}

VulkanCommandPool::~VulkanCommandPool() {
    device.getHandle().destroyCommandPool(handle);
}

VulkanCommandBuffer &VulkanCommandPool::getCommandBuffer() {
    if (bufferCount < commandBuffers.size()) {
        return *commandBuffers.at(bufferCount++);
    }
    commandBuffers.emplace_back(std::make_unique<VulkanCommandBuffer>(*this));
    bufferCount++;
    return *commandBuffers.back();
}

} // namespace Elements
