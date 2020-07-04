#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanSurface {
  public:
    static VulkanSurface *getInstance();

    void destroy();

  private:
    VulkanSurface() = default;
    ~VulkanSurface();
};

} // namespace Elements
