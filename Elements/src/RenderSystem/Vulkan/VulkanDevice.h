#pragma once

#include "VulkanQueue.h"

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanFramebuffer;
class VulkanRenderTarget;
class VulkanRenderPass;

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
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

    void createFramebuffers(const VulkanRenderTarget &renderTarget, VulkanRenderPass &renderPass);

    void clearFramebuffers();

    vk::Device getHandle() const {
        return handle;
    }

    vk::PhysicalDevice &getPhysicalDevice() {
        return physicalDevice;
    }

    QueueFamilyIndices getQueueFamilyIndices() {
        return queueFamilyIndices;
    }

    VulkanQueue &getGraphicsQueue() {
        return queues[0];
    }
    VulkanQueue &getPresentQueue() {
        return queues[1];
    }

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

    // First is graphics and second is present
    std::vector<VulkanQueue> queues;

    std::vector<VulkanFramebuffer> framebuffers;

    const std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
};

} // namespace Elements
