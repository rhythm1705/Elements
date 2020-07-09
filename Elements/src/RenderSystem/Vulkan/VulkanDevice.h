#pragma once

#include "RenderSystem/Vulkan/Queue/VulkanQueue.h"
#include "RenderSystem/Vulkan/VulkanSwapChain.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanDevice {
  public:
    static VulkanDevice *getInstance();

    void init();

    vk::PhysicalDevice &getVulkanPhysicalDevice() { return physicalDevice; }
    vk::Device &getVulkanDevice() { return logicalDevice; }

    VulkanQueue::QueueFamilyIndices getQueueFamilyIndices() { return queueFamilyIndices; }

    VulkanSwapChain::SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice physicalDevice);
    VulkanQueue::QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice physicalDevice);

    void destroy();

  private:
    VulkanDevice() = default;
    ~VulkanDevice(){};

    void pickPhysicalDevice();
    void createLogicalDevice();

    bool isDeviceSuitable(vk::PhysicalDevice physicalDevice);
    bool checkDeviceExtensionSupport(vk::PhysicalDevice physicalDevice);

    static VulkanDevice *vulkanDevice;

    vk::PhysicalDevice physicalDevice;
    vk::Device logicalDevice;

    const std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    VulkanQueue::QueueFamilyIndices queueFamilyIndices;
};

} // namespace Elements
