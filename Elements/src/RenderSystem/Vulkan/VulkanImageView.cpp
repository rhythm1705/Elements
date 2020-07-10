#include "VulkanImageView.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {
VulkanImageViews::VulkanImageViews(VulkanSwapChain *swapChain) {
    auto &swapChainImages = swapChain->getSwapChainImages();
    auto &swapChainImageFormat = swapChain->getSwapChainImageFormat();
    swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++) {
        vk::ImageViewCreateInfo createInfo(
          vk::ImageViewCreateFlags(), swapChainImages[i], vk::ImageViewType::e2D, swapChainImageFormat,
          vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG,
                               vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA),
          vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
        if (VulkanDevice::getInstance()->getVulkanDevice().createImageView(
              &createInfo, nullptr, &swapChainImageViews[i])
            != vk::Result::eSuccess) {
            ELMT_CORE_ERROR("Failed to create vulkan swapchain image views!");
        }
    }
}

VulkanImageViews::~VulkanImageViews() {
    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        VulkanDevice::getInstance()->getVulkanDevice().destroyImageView(swapChainImageViews[i]);
    }
}

} // namespace Elements