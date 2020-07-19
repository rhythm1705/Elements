#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanShaderModule;

class VulkanPipelineLayout {
  public:
    VulkanPipelineLayout(VulkanDevice &device, const std::vector<VulkanShaderModule *> &shaderModules);
    ~VulkanPipelineLayout();

    vk::PipelineLayout getHandle() const;

    const std::vector<VulkanShaderModule *> &getShaderModules() const;

  private:
    VulkanDevice &device;

    vk::PipelineLayout handle;

    // The shader modules that this pipeline layout uses
    std::vector<VulkanShaderModule *> shaderModules;
};

} // namespace Elements
