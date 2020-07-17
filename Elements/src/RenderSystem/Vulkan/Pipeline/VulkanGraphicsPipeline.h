#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;

class VulkanGraphicsPipeline {
  public:
    VulkanGraphicsPipeline(VulkanDevice &device, const char *vertexShader, const char *fragmentShader, const vk::Extent2D &swapChainExtent);
    ~VulkanGraphicsPipeline();

    vk::Pipeline getPipeline();
    vk::PipelineLayout getPipelineLayout();

  private:
    VulkanDevice &device;

    vk::Pipeline handle;
    vk::PipelineLayout pipelineLayout;
};

} // namespace Elements
