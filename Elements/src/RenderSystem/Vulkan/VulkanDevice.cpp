#include "VulkanDevice.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"

namespace Elements {
VulkanDevice *vulkanDevice = nullptr;

VulkanDevice *VulkanDevice::getInstance() {
    if (!vulkanDevice) {
        vulkanDevice = new VulkanDevice;
    }
    return vulkanDevice;
}

void VulkanDevice::init() {
    pickPhysicalDevice();
    createLogicalDevice();
}

void VulkanDevice::pickPhysicalDevice() {
    std::vector<vk::PhysicalDevice> devices
      = VulkanInstance::getInstance()->getVulkanInstance().enumeratePhysicalDevices();
    if (devices.empty()) {
        ELMT_CORE_ERROR("Failed to find GPUs with Vulkan support !");
    }
    for (const auto &device : devices) {
        if (isDeviceSuitable(device)) {
            physicalDevice = device;
            break;
        }
    }
    if (!physicalDevice) {
        ELMT_CORE_ERROR("Failed to find a suitable GPU!");
    }
}

void VulkanDevice::createLogicalDevice() {
    VulkanQueue::QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
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
                                          queueCreateInfos.data(), 0, nullptr,
                                          static_cast<uint32_t>(deviceExtensions.size()),
                                          deviceExtensions.data(), &deviceFeatures);
    if (physicalDevice.createDevice(&deviceCreateInfo, nullptr, &logicalDevice) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create logical device!");
    }
}

bool VulkanDevice::isDeviceSuitable(vk::PhysicalDevice physicalDevice) {
    VulkanQueue::QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
    bool swapChainAdequate = false;
    if (extensionsSupported) {
        VulkanSwapChain::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }
    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

VulkanQueue::QueueFamilyIndices VulkanDevice::findQueueFamilies(vk::PhysicalDevice physicalDevice) {
    std::vector<vk::QueueFamilyProperties> queueFamilies = physicalDevice.getQueueFamilyProperties();
    VulkanQueue::QueueFamilyIndices indices;
    int i = 0;
    auto surface = VulkanSurface::getInstance()->getVulkanSurface();
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

VulkanSwapChain::SwapChainSupportDetails VulkanDevice::querySwapChainSupport(vk::PhysicalDevice physicalDevice) {
    VulkanSwapChain::SwapChainSupportDetails details;
    auto surface = VulkanSurface::getInstance()->getVulkanSurface();
    details.capabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
    details.formats = physicalDevice.getSurfaceFormatsKHR(surface);
    details.presentModes = physicalDevice.getSurfacePresentModesKHR(surface);
    return details;
}

void VulkanDevice::destroy() { logicalDevice.destroy(); }

} // namespace Elements