#pragma once

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
    VulkanDevice(vk::Instance instance, vk::SurfaceKHR surface);
    ~VulkanDevice();

    vk::Device getHandle() const { return handle; }

    vk::PhysicalDevice &getPhysicalDevice() { return physicalDevice; }

    QueueFamilyIndices getQueueFamilyIndices() { return queueFamilyIndices; }

    SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);

  private:
    void pickPhysicalDevice(vk::Instance instance, vk::SurfaceKHR surface);
    void createLogicalDevice(vk::SurfaceKHR surface);

    bool isDeviceSuitable(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);
    bool checkDeviceExtensionSupport(vk::PhysicalDevice physicalDevice);
    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);

    vk::Device handle;

    vk::PhysicalDevice physicalDevice;

    QueueFamilyIndices queueFamilyIndices;

    const std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
};

} // namespace Elements
