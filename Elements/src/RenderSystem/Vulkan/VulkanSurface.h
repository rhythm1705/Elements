#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanSurface {
  public:
    static VulkanSurface *getInstance();

    void init();

    vk::SurfaceKHR &getVulkanSurface() { return surface; }

    void destroy();

  private:
    VulkanSurface() = default;
    ~VulkanSurface(){};

    static VulkanSurface *vulkanSurface;

    vk::SurfaceKHR surface;
};

} // namespace Elements
