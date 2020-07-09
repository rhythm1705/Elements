#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {
class VulkanGraphicsPipeline {
  public:
    VulkanGraphicsPipeline(const char *vertexShader, const char *fragmentShader, const vk::Extent2D &swapChainExtent);
    ~VulkanGraphicsPipeline();

    vk::Pipeline getPipeline();
    vk::PipelineLayout getPipelineLayout();

  private:
    vk::Pipeline pipeline;
    vk::PipelineLayout pipelineLayout;
};

} // namespace Elements
