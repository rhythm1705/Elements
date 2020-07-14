#pragma once

#include <vulkan/vulkan.hpp>


namespace Elements {

class VulkanInstance {
  public:
    VulkanInstance(const std::string &appName, const int appVersion, const std::string &engineName, const int engineVersion);
    ~VulkanInstance();

    vk::Instance getHandle() { return handle; };
    vk::SurfaceKHR getSurface() { return surface; };

  private:
    std::vector<const char *> getRequiredExtensions();

    vk::Instance handle;
    vk::SurfaceKHR surface;
};

} // namespace Elements
