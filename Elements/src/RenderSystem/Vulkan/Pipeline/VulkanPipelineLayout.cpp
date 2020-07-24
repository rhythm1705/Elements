#include "VulkanPipelineLayout.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"
#include "RenderSystem/Vulkan/VulkanShaderModule.h"

namespace Elements {

VulkanPipelineLayout::VulkanPipelineLayout(VulkanDevice &device, const std::vector<VulkanShaderModule *> &shaderModules) :
device{ device }, shaderModules{ shaderModules } {
    vk::PipelineLayoutCreateInfo pipelineLayoutInfo(vk::PipelineLayoutCreateFlags(), 0, nullptr, 0, nullptr);
    if (device.getHandle().createPipelineLayout(&pipelineLayoutInfo, nullptr, &handle) != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create vulkan pipeline layout!");
    }
}

VulkanPipelineLayout::~VulkanPipelineLayout() {
    if (handle) {
        device.getHandle().destroyPipelineLayout(handle);
    }
}

vk::PipelineLayout VulkanPipelineLayout::getHandle() const {
    return handle;
}

const std::vector<VulkanShaderModule *> &VulkanPipelineLayout::getShaderModules() const {
    return shaderModules;
}

} // namespace Elements
