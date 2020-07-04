#include "VulkanInstance.h"

namespace Elements {
VulkanInstance *vulkanInstance = nullptr;

VulkanInstance *VulkanInstance::getInstance(const std::string &appName,
                                            const int appVersion,
                                            const std::string &engineName,
                                            const int engineVersion) {
    if (!vulkanInstance) {
        vulkanInstance = new VulkanInstance();
        vulkanInstance->init(appName, appVersion, engineName, engineVersion);
    }
    return vulkanInstance;
}

void VulkanInstance::init(const std::string &appName, const int appVersion, const std::string &engineName, const int engineVersion) {
    vk::ApplicationInfo appInfo(appName.c_str(), appVersion, engineName.c_str(), engineVersion, VK_API_VERSION_1_2);
    auto extensions = getRequiredExtensions();
    vk::InstanceCreateInfo createInfo(vk::InstanceCreateFlags(), &appInfo, 0, {},
                                      static_cast<uint32_t>(extensions.size()), extensions.data());
    if (vk::createInstance(&createInfo, nullptr, &instance) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create vulkan instance!");
    }
}

std::vector<const char *> VulkanInstance::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    return extensions;
}

void VulkanInstance::destroy() {
    instance.destroy();
    delete vulkanInstance;
    vulkanInstance = nullptr;
}

} // namespace Elements