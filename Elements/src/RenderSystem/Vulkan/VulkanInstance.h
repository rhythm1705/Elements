#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>


namespace Elements {

class VulkanInstance {
  public:
    static VulkanInstance *getInstance();

    void init(const std::string &appName, const int appVersion, const std::string &engineName, const int engineVersion);

    vk::Instance getVulkanInstance() { return instance; };

    void destroy();

  private:
    VulkanInstance() = default;
    ~VulkanInstance(){};

    std::vector<const char *> getRequiredExtensions();

    static VulkanInstance *vulkanInstance;

    vk::Instance instance;
};

} // namespace Elements
