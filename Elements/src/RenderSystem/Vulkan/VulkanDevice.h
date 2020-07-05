#pragma once

#include <optional>
#include <vulkan/vulkan.hpp>

namespace Elements {
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

class VulkanDevice {
  public:
    static VulkanDevice *getInstance();

    vk::PhysicalDevice &getVulkanPhysicalDevice() { return physicalDevice; }
    vk::Device &getVulkanDevice() { return logicalDevice; }

    void destroy();

  private:
    VulkanDevice() = default;
    ~VulkanDevice(){};

    void init();

    void pickPhysicalDevice();
    void createLogicalDevice();

    bool isDeviceSuitable(vk::PhysicalDevice physicalDevice);
    bool checkDeviceExtensionSupport(vk::PhysicalDevice physicalDevice);
    SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice physicalDevice);
    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice physicalDevice);

    static VulkanDevice *vulkanDevice;

    vk::PhysicalDevice physicalDevice;
    vk::Device logicalDevice;

    const std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
};

} // namespace Elements
