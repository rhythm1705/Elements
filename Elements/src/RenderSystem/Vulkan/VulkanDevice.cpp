#include "VulkanDevice.h"

#include "VulkanFrameBuffer.h"
#include "VulkanInstance.h"
#include "VulkanSwapChain.h"

namespace Elements {

VulkanDevice::VulkanDevice(vk::Instance instance, vk::SurfaceKHR surface) {
    pickPhysicalDevice(instance, surface);
    createLogicalDevice(surface);
    queues.reserve(2);
    queues.emplace_back(*this, queueFamilyIndices.graphicsFamily.value(), false);
    queues.emplace_back(*this, queueFamilyIndices.presentFamily.value(), true);
}

VulkanDevice::~VulkanDevice() {
    if (handle) {
        handle.destroy();
    }
}

void VulkanDevice::pickPhysicalDevice(vk::Instance instance, vk::SurfaceKHR surface) {
    std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();
    if (devices.empty()) {
        ELMT_CORE_ERROR("Failed to find GPUs with Vulkan support !");
    }
    for (const auto &device : devices) {
        if (isDeviceSuitable(device, surface)) {
            physicalDevice = device;
            break;
        }
    }
    if (!physicalDevice) {
        ELMT_CORE_ERROR("Failed to find a suitable GPU!");
    }
}

void VulkanDevice::createLogicalDevice(vk::SurfaceKHR surface) {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies
      = { indices.graphicsFamily.value(), indices.presentFamily.value() };
    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        vk::DeviceQueueCreateInfo queueCreateInfo(vk::DeviceQueueCreateFlags(), queueFamily, 1, &queuePriority);
        queueCreateInfos.push_back(queueCreateInfo);
    }
    vk::PhysicalDeviceFeatures deviceFeatures{};
    vk::DeviceCreateInfo deviceCreateInfo(vk::DeviceCreateFlags(),
                                          static_cast<uint32_t>(queueCreateInfos.size()),
                                          queueCreateInfos.data(),
                                          0,
                                          nullptr,
                                          static_cast<uint32_t>(deviceExtensions.size()),
                                          deviceExtensions.data(),
                                          &deviceFeatures);
    if (physicalDevice.createDevice(&deviceCreateInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create logical device!");
    }
}

bool VulkanDevice::isDeviceSuitable(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface) {
    queueFamilyIndices = findQueueFamilies(physicalDevice, surface);
    bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    return queueFamilyIndices.isComplete() && extensionsSupported && swapChainAdequate;
}

QueueFamilyIndices VulkanDevice::findQueueFamilies(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface) {
    std::vector<vk::QueueFamilyProperties> queueFamilies = physicalDevice.getQueueFamilyProperties();
    QueueFamilyIndices indices;
    int i = 0;
    for (const auto &queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphicsFamily = i;
        }
        vk::Bool32 presentSupport = physicalDevice.getSurfaceSupportKHR(i, surface);
        if (presentSupport) {
            indices.presentFamily = i;
        }
        if (indices.isComplete()) {
            break;
        }
        i++;
    }
    return indices;
}

bool VulkanDevice::checkDeviceExtensionSupport(vk::PhysicalDevice physicalDevice) {
    std::vector<vk::ExtensionProperties> availableExtensions
      = physicalDevice.enumerateDeviceExtensionProperties();
    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
    for (const auto &extension : availableExtensions) {
        requiredExtensions.erase(std::string(extension.extensionName));
    }
    return requiredExtensions.empty();
}

void VulkanDevice::clearFramebuffers() {
    framebuffers.clear();
}

SwapChainSupportDetails
VulkanDevice::querySwapChainSupport(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface) {
    SwapChainSupportDetails details;
    details.capabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
    details.formats = physicalDevice.getSurfaceFormatsKHR(surface);
    details.presentModes = physicalDevice.getSurfacePresentModesKHR(surface);
    return details;
}

} // namespace Elements