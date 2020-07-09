#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanSyncObjects {
  public:
    VulkanSyncObjects(uint32_t imageCount);
    ~VulkanSyncObjects();

    const std::vector<vk::Semaphore> &getImageAvailableSemaphores() const {
        return imageAvailableSemaphores;
    };
    const std::vector<vk::Semaphore> &getRenderFinishedSemaphores() const {
        return renderFinishedSemaphores;
    };
    const std::vector<vk::Fence> &getInFlightFences() const { return inFlightFences; };
    const std::vector<vk::Fence> &getImagesInFlightFences() const { return imagesInFlight; };


  private:
    std::vector<vk::Semaphore> imageAvailableSemaphores;
    std::vector<vk::Semaphore> renderFinishedSemaphores;
    std::vector<vk::Fence> inFlightFences;
    std::vector<vk::Fence> imagesInFlight;

    uint32_t imageCount = -1;
};

} // namespace Elements
