#pragma once

#include <vulkan/vulkan.hpp>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };

namespace Elements {
class VulkanValidationLayers {
  public:
    VulkanValidationLayers();
    ~VulkanValidationLayers();

    static void setupDebugMessenger();
    bool checkValidationLayersSupport();
    static void populateDebugMessengerCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT &createInfo);
    static vk::DispatchLoaderDynamic &getDynamicDispatcher() { return dispatcher; }

  private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                                                        void *userData);

    static vk::DebugUtilsMessengerEXT debugMessenger;
    static vk::DispatchLoaderDynamic dispatcher;
};

} // namespace Elements
