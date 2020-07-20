#include "VulkanRenderContext.h"

#include "VulkanCommandBuffers.h"
#include "VulkanDevice.h"
#include "VulkanQueue.h"
#include "VulkanRenderFrame.h"
#include "VulkanSwapChain.h"

namespace Elements {
VulkanRenderContext::VulkanRenderContext(VulkanDevice &device, vk::SurfaceKHR surface, uint32_t width, uint32_t height) :
device{ device }, surfaceExtent{ width, height } {
}
VulkanRenderContext::~VulkanRenderContext() {
}
VulkanDevice &VulkanRenderContext::getDevice() {
    // TODO: insert return statement here
}
vk::Format VulkanRenderContext::getFormat() {
    return vk::Format();
}
VulkanSwapchain &VulkanRenderContext::getSwapchain() {
    // TODO: insert return statement here
}
vk::Extent2D VulkanRenderContext::getSurface_extent() const {
    return vk::Extent2D();
}
uint32_t VulkanRenderContext::getActiveFrameIndex() const {
    return uint32_t();
}
std::vector<std::unique_ptr<VulkanRenderFrame>> &VulkanRenderContext::getRenderFrames() {
    // TODO: insert return statement here
}
void VulkanRenderContext::requestPresentMode(const vk::PresentModeKHR presentMode) {
}
void VulkanRenderContext::requestImageFormat(const vk::Format format) {
}
void VulkanRenderContext::setPresentModePriority(const std::vector<vk::PresentModeKHR> &presentModePriorityList) {
}
void VulkanRenderContext::setSurfaceFormatPriority(const std::vector<vk::SurfaceFormatKHR> &surfaceFormatPriorityList) {
}
void VulkanRenderContext::prepare() {
}
void VulkanRenderContext::updateSwapchain(const vk::Extent2D &extent) {
}
void VulkanRenderContext::updateSwapchain(const uint32_t imageCount) {
}
void VulkanRenderContext::updateSwapchain(const std::set<vk::ImageUsageFlagBits> &imageUsageFlags) {
}
void VulkanRenderContext::updateSwapchain(const vk::Extent2D &extent,
                                          const vk::SurfaceTransformFlagBitsKHR transform) {
}
bool VulkanRenderContext::hasSwapchain() {
    return false;
}
void VulkanRenderContext::recreate() {
}
void VulkanRenderContext::recreateSwapchain() {
}
VulkanCommandBuffer &VulkanRenderContext::begin() {
    // TODO: insert return statement here
}
void VulkanRenderContext::submit(VulkanCommandBuffer &commandBuffer) {
}
vk::Semaphore VulkanRenderContext::beginFrame() {
    return vk::Semaphore();
}
vk::Semaphore VulkanRenderContext::submit(const VulkanQueue &queue,
                                          const VulkanCommandBuffer &commandBuffer,
                                          vk::Semaphore waitSemaphore,
                                          vk::PipelineStageFlags wait_pipelineStage) {
    return vk::Semaphore();
}
void VulkanRenderContext::submit(const VulkanQueue &queue, const VulkanCommandBuffer &commandBuffer) {
}
void VulkanRenderContext::waitFrame() {
}
void VulkanRenderContext::endFrame(vk::Semaphore semaphore) {
}
VulkanRenderFrame &VulkanRenderContext::getActiveFrame() {
    // TODO: insert return statement here
}
uint32_t VulkanRenderContext::getActiveFrameIndex() {
    return uint32_t();
}
VulkanRenderFrame &VulkanRenderContext::getLastRenderedFrame() {
    // TODO: insert return statement here
}
vk::Semaphore VulkanRenderContext::requestSemaphore() {
    return vk::Semaphore();
}
} // namespace Elements
