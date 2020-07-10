#include "VulkanValidationLayers.h"

#include "VulkanInstance.h"

namespace Elements {

vk::DebugUtilsMessengerEXT VulkanValidationLayers::debugMessenger;
vk::DispatchLoaderDynamic VulkanValidationLayers::dispatcher;

VulkanValidationLayers::VulkanValidationLayers() {
    if (enableValidationLayers && !checkValidationLayersSupport()) {
        ELMT_CORE_CRITICAL("Validation Layers requested but not supported.");
    }
}

VulkanValidationLayers::~VulkanValidationLayers() {}

void VulkanValidationLayers::destroyDebugMessenger() {
    VulkanInstance::getInstance()->getVulkanInstance().destroyDebugUtilsMessengerEXT(
      debugMessenger, nullptr, dispatcher);
}

bool VulkanValidationLayers::checkValidationLayersSupport() {
    std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
    for (const char *layerName : validationLayers) {
        bool layerFound = false;
        for (const auto &layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}

void VulkanValidationLayers::setupDebugMessenger() {
    if (!enableValidationLayers) return;
    vk::DebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    /*const vk::DynamicLoader dl;
    const PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr
      = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");*/

    dispatcher = vk::DispatchLoaderDynamic(VulkanInstance::getInstance()->getVulkanInstance(), vkGetInstanceProcAddr);

    debugMessenger = VulkanInstance::getInstance()->getVulkanInstance().createDebugUtilsMessengerEXT(
      createInfo, nullptr, dispatcher);
    ELMT_CORE_TRACE("Validation Layers Enabled!");
}

void VulkanValidationLayers::populateDebugMessengerCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo.setMessageSeverity(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                                  | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                                  | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
    createInfo.setMessageType(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                              | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
                              | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance);
    createInfo.setPfnUserCallback(debugCallback);
}


VKAPI_ATTR VkBool32 VKAPI_CALL
VulkanValidationLayers::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                      VkDebugUtilsMessageTypeFlagsEXT messageType,
                                      const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                                      void *userData) {
    ELMT_CORE_ERROR("Message: {0}\n ", callbackData->pMessage);
    return VK_FALSE;
}

} // namespace Elements
