#include "VulkanSwapChain.h"

#include "Core/Application.h"
#include "RenderSystem/Vulkan/VulkanDevice.h"
#include "VulkanQueue.h"

#include <GLFW/glfw3.h>

namespace Elements {
VulkanSwapchain::VulkanSwapchain(VulkanDevice &device, vk::SurfaceKHR surface) :
device{ device }, surface{ surface } {

    SwapChainSupportDetails swapChainSupport
      = device.querySwapChainSupport(device.getPhysicalDevice(), surface);

    vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0
        && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    vk::SwapchainCreateInfoKHR createInfo(vk::SwapchainCreateFlagsKHR(),
                                          surface,
                                          imageCount,
                                          surfaceFormat.format,
                                          surfaceFormat.colorSpace,
                                          extent,
                                          1,
                                          vk::ImageUsageFlagBits::eColorAttachment);

    QueueFamilyIndices indices = device.getQueueFamilyIndices();
    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
    if (indices.graphicsFamily != indices.presentFamily) {
        // Images can be used across multiple queue families without explicit ownership transfers.
        createInfo.setImageSharingMode(vk::SharingMode::eConcurrent);
        createInfo.setQueueFamilyIndexCount(2);
        createInfo.setPQueueFamilyIndices(queueFamilyIndices);
    } else {
        // An image is owned by one queue family at a time and ownership must be explicitly
        // transferred before using it in another queue family. This option offers the best
        // performance.
        createInfo.setImageSharingMode(vk::SharingMode::eExclusive);
    }

    createInfo.setPreTransform(swapChainSupport.capabilities.currentTransform);
    createInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
    createInfo.setPresentMode(presentMode);
    createInfo.setClipped(VK_TRUE);
    createInfo.setOldSwapchain(nullptr);

    if (device.getHandle().createSwapchainKHR(&createInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to create swap chain!");
    }

    swapChainImages = device.getHandle().getSwapchainImagesKHR(handle);
    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

VulkanSwapchain::~VulkanSwapchain() {
    device.getHandle().destroy(handle);
}

vk::Result
VulkanSwapchain::acquireNextImage(uint32_t &imageIndex, vk::Semaphore imageAcquiredSemaphore, vk::Fence fence) {
    return device.getHandle().acquireNextImageKHR(handle,
                                                  std::numeric_limits<uint64_t>::max(),
                                                  imageAcquiredSemaphore,
                                                  fence,
                                                  &imageIndex);
}

vk::SurfaceFormatKHR
VulkanSwapchain::chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR> &availableFormats) {
    for (const auto &availableFormat : availableFormats) {
        if (availableFormat.format == vk::Format::eB8G8R8A8Srgb
            && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

vk::PresentModeKHR
VulkanSwapchain::chooseSwapPresentMode(const std::vector<vk::PresentModeKHR> &availablePresentModes) {
    for (const auto &availablePresentMode : availablePresentModes) {
        if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
            return availablePresentMode;
        }
    }
    return vk::PresentModeKHR::eFifo;
}

vk::Extent2D VulkanSwapchain::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        auto window = Application::get().getWindow().getWindowPtr();
        glfwGetFramebufferSize(window, &width, &height);
        vk::Extent2D actualExtent(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

} // namespace Elements