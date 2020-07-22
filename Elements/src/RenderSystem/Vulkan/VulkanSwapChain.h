#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanDevice;

class VulkanSwapchain {
  public:
    VulkanSwapchain(VulkanDevice &device, vk::SurfaceKHR surface);
    ~VulkanSwapchain();

    vk::SurfaceKHR &getSurface() {
        return surface;
    }
    vk::SwapchainKHR &getSwapChain() {
        return handle;
    }
    std::vector<vk::Image> &getSwapChainImages() {
        return swapChainImages;
    }
    vk::Format &getSwapChainImageFormat() {
        return swapChainImageFormat;
    }
    vk::Extent2D &getswapChainExtent() {
        return swapChainExtent;
    }

    vk::Result acquireNextImage(uint32_t &imageIndex, vk::Semaphore imageAcquired_Semaphore, vk::Fence fence);

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats);
    vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes);
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities);

  private:
    vk::SwapchainKHR handle;

    VulkanDevice &device;

    vk::SurfaceKHR surface;

    std::vector<vk::Image> swapChainImages;
    vk::Format swapChainImageFormat;
    vk::Extent2D swapChainExtent;
};
} // namespace Elements
