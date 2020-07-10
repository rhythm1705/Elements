#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanSwapChain {
  public:
    VulkanSwapChain();
    ~VulkanSwapChain();

    vk::SwapchainKHR &getSwapChain() { return swapChain; }
    std::vector<vk::Image> &getSwapChainImages() { return swapChainImages; }
    vk::Format &getSwapChainImageFormat() { return swapChainImageFormat; }
    vk::Extent2D &getswapChainExtent() { return swapChainExtent; }

    vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats);
    vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes);
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities);

    struct SwapChainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

  private:
    vk::SwapchainKHR swapChain;
    std::vector<vk::Image> swapChainImages;
    vk::Format swapChainImageFormat;
    vk::Extent2D swapChainExtent;
};
} // namespace Elements
