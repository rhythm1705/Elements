#include "VulkanRenderPass.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"

namespace Elements {

void VulkanRenderPass::destroy() {
    VulkanDevice::getInstance()->getVulkanDevice().destroyRenderPass(renderPass);
}

} // namespace Elements
