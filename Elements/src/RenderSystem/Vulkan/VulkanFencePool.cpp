#include "VulkanFencePool.h"

#include "VulkanDevice.h"

namespace Elements {

VulkanFencePool::VulkanFencePool(VulkanDevice &device) : device{ device } {}

VulkanFencePool::~VulkanFencePool() {
    wait();
    reset();
    // Destroy all fences
    for (VkFence fence : fences) {
        device.getHandle().destroyFence(fence);
    }
    fences.clear();
}

vk::Fence VulkanFencePool::requestFence() {
    // Check if there is an available fence
    if (activeFenceCount < fences.size()) {
        return fences.at(activeFenceCount++);
    }
    // Create new fence
    vk::Fence fence;
    vk::FenceCreateInfo createInfo;
    if (device.getHandle().createFence(&createInfo, nullptr, &fence) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create fence.");
    }
    fences.push_back(fence);
    activeFenceCount++;
    return fence;
}

vk::Result VulkanFencePool::wait(uint32_t timeout) const {
    if (activeFenceCount < 1 || fences.empty()) {
        return vk::Result::eSuccess;
    }
    return device.getHandle().waitForFences(activeFenceCount, fences.data(), true, timeout);
}

vk::Result VulkanFencePool::reset() {
    if (activeFenceCount < 1 || fences.empty()) {
        return vk::Result::eSuccess;
    }
    vk::Result result = device.getHandle().resetFences(activeFenceCount, fences.data());
    if (result != vk::Result::eSuccess) {
        return result;
    }
    activeFenceCount = 0;
    return vk::Result::eSuccess;
}

} // namespace Elements
