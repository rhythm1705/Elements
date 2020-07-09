#include "VulkanSyncObjects.h"

#include "VulkanDevice.h"

namespace Elements {

VulkanSyncObjects::VulkanSyncObjects(uint32_t imageCount) : imageCount(imageCount) {
    imageAvailableSemaphores.resize(imageCount);
    renderFinishedSemaphores.resize(imageCount);
    inFlightFences.resize(imageCount);
    imagesInFlight.resize(imageCount);
    vk::SemaphoreCreateInfo semaphoreInfo;
    vk::FenceCreateInfo fenceInfo(vk::FenceCreateFlagBits::eSignaled);
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    for (size_t i = 0; i < imageCount; i++) {
        if (device.createSemaphore(&semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != vk::Result::eSuccess
            || device.createSemaphore(&semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != vk::Result::eSuccess
            || device.createFence(&fenceInfo, nullptr, &inFlightFences[i]) != vk::Result::eSuccess) {
            ELMT_CORE_ERROR("failed to create synchronization objects for a frame!");
        }
    }
}

VulkanSyncObjects::~VulkanSyncObjects() {
    auto &device = VulkanDevice::getInstance()->getVulkanDevice();
    for (size_t i = 0; i < imageCount; i++) {
        device.destroySemaphore(renderFinishedSemaphores[i]);
        device.destroySemaphore(imageAvailableSemaphores[i]);
        device.destroyFence(inFlightFences[i]);
    }
}

} // namespace Elements
