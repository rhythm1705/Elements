#pragma once

#include "VulkanPipelineState.h"

#include <vulkan/vulkan.hpp>


namespace Elements {

class VulkanDevice;

class VulkanGraphicsPipeline {
  public:
    VulkanGraphicsPipeline(VulkanDevice &device, VulkanPipelineState &pipelineState);
    ~VulkanGraphicsPipeline();

    vk::Pipeline getHandle();
    VulkanPipelineState getPipelineState();

  private:
    VulkanDevice &device;

    vk::Pipeline handle;

    VulkanPipelineState pipelineState;
};

} // namespace Elements
