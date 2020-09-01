#pragma once

#include "Vulkan/Pipeline/VulkanGraphicsPipeline.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanRenderContext.h"
#include "Vulkan/VulkanRenderPass.h"

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanRenderer {
  public:
    static void init();

    static void drawTriangle();

    static void update();
    static void resize(const uint32_t width, const uint32_t height);

  private:
    static vk::SurfaceKHR surface;
    static std::unique_ptr<VulkanInstance> instance;
    static std::unique_ptr<VulkanDevice> device;
    static std::unique_ptr<VulkanRenderContext> context;
    static std::unique_ptr<VulkanRenderPass> renderPass;
    static std::unique_ptr<VulkanGraphicsPipeline> pipeline;
};

} // namespace Elements
