#include "VulkanQueue.h"

#include "VulkanCommandBuffers.h"
#include "VulkanDevice.h"

namespace Elements {
VulkanQueue::VulkanQueue(VulkanDevice &device, uint32_t familyIndex, vk::Bool32 canPresent) :
device{ device }, familyIndex{ familyIndex }, canPresent{ canPresent } {
    device.getHandle().getQueue(familyIndex, 0, &handle);
}

VulkanQueue::~VulkanQueue() {
}

const VulkanDevice &VulkanQueue::getDevice() const {
    return device;
}

vk::Queue VulkanQueue::getHandle() const {
    return handle;
}

uint32_t VulkanQueue::getFamilyIndex() const {
    return familyIndex;
}

vk::Bool32 VulkanQueue::supportPresent() const {
    return canPresent;
}

void VulkanQueue::submit(const std::vector<vk::SubmitInfo> &submitInfos, vk::Fence fence) const {
    handle.submit(submitInfos, fence);
}

void VulkanQueue::submit(const VulkanCommandBuffer &commandBuffer, vk::Fence fence) const {
    vk::SubmitInfo submitInfo;
    submitInfo.setCommandBufferCount(1);
    submitInfo.setPCommandBuffers(&commandBuffer.getCommandBuffer());
    submit({ submitInfo }, fence);
}

vk::Result VulkanQueue::present(const vk::PresentInfoKHR &presentInfo) const {
    return handle.presentKHR(presentInfo);
}

void VulkanQueue::waitIdle() const {
    handle.waitIdle();
}

} // namespace Elements
