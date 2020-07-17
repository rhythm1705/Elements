#include "VulkanSemaphorePool.h"

#include "VulkanDevice.h"

namespace Elements {

VulkanSemaphorePool::VulkanSemaphorePool(VulkanDevice &device) : device{ device } {}

VulkanSemaphorePool::~VulkanSemaphorePool() {
    reset();
    // Destroy all semaphores
    for (vk::Semaphore semaphore : semaphores) {
        device.getHandle().destroySemaphore(semaphore);
    }
    semaphores.clear();
}

vk::Semaphore VulkanSemaphorePool::requestSemaphore() {
    // Check if there is an available semaphore
    if (activeSemaphoreCount < semaphores.size()) {
        return semaphores.at(activeSemaphoreCount++);
    }
    // Create new semaphore
    vk::Semaphore semaphore;
    vk::SemaphoreCreateInfo createInfo;
    if (device.getHandle().createSemaphore(&createInfo, nullptr, &semaphore) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create semaphore.");
    }
    semaphores.push_back(semaphore);
    activeSemaphoreCount++;
    return semaphore;
}

uint32_t VulkanSemaphorePool::getActiveSemaphoreCount() const { return activeSemaphoreCount; }

void VulkanSemaphorePool::reset() { activeSemaphoreCount = 0; }

} // namespace Elements
