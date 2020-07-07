#include "VulkanStandardRenderPass.h"

namespace Elements {
VulkanStandardRenderPass *VulkanStandardRenderPass::getInstance() { return nullptr; }
void VulkanStandardRenderPass::init(vk::Format &swapChainImageFormat) {}
void VulkanStandardRenderPass::destroy() {}
} // namespace Elements
