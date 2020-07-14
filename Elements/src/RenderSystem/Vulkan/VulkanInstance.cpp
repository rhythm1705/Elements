#include "VulkanInstance.h"

#include "Core/Application.h"
#include "VulkanValidationLayers.h"

#include <GLFW/glfw3.h>

namespace Elements {

VulkanInstance::VulkanInstance(const std::string &appName,
                               const int appVersion,
                               const std::string &engineName,
                               const int engineVersion) {
    vk::ApplicationInfo appInfo(appName.c_str(), appVersion, engineName.c_str(), engineVersion, VK_API_VERSION_1_2);
    auto extensions = getRequiredExtensions();
    vk::InstanceCreateInfo createInfo(vk::InstanceCreateFlags(), &appInfo, 0, {},
                                      static_cast<uint32_t>(extensions.size()), extensions.data());

    vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (enableValidationLayers) {
        createInfo.setEnabledLayerCount(static_cast<uint32_t>(validationLayers.size()));
        createInfo.setPpEnabledLayerNames(validationLayers.data());

        VulkanValidationLayers::populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.setPNext((VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo);
    } else {
        createInfo.setEnabledLayerCount(0);
        createInfo.setPNext(nullptr);
    }

    if (vk::createInstance(&createInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create vulkan instance!");
    }

    auto window = Application::get().getWindow().getWindowPtr();
    if (glfwCreateWindowSurface(handle, window, nullptr, reinterpret_cast<VkSurfaceKHR *>(&surface)) != VK_SUCCESS) {
        ELMT_CORE_ERROR("Failed to create vulkan window surface!");
    }
}

VulkanInstance::~VulkanInstance() {
    if (handle != VK_NULL_HANDLE) {
        handle.destroySurfaceKHR(surface);
        handle.destroy();
    }
}

std::vector<const char *> VulkanInstance::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
}

} // namespace Elements