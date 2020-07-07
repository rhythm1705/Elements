#pragma once

#include "RenderSystem/Vulkan/VulkanSwapChain.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanImageViews {
  public:
    VulkanImageViews(VulkanSwapChain *swapChain);
    ~VulkanImageViews();

    std::vector<vk::ImageView> getSwapChainImageViews() { return swapChainImageViews; }

  private:
    std::vector<vk::ImageView> swapChainImageViews;
};

} // namespace Elements
