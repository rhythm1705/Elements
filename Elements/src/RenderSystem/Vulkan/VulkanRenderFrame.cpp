#include "VulkanRenderFrame.h"

#include "VulkanCommandBuffers.h"
#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanFencePool.h"
#include "VulkanRenderTarget.h"
#include "VulkanSemaphorePool.h"

namespace Elements {

VulkanRenderFrame::VulkanRenderFrame(VulkanDevice &device, std::unique_ptr<VulkanRenderTarget> &&renderTarget) :
device{ device }, fencePool{ device }, semaphorePool{ device }, renderTarget{ std::move(renderTarget) } {
}

VulkanRenderFrame::~VulkanRenderFrame() {
}

VulkanDevice &VulkanRenderFrame::getDevice() {
    return device;
}

void VulkanRenderFrame::reset() {
    fencePool.wait();
    fencePool.reset();
    semaphorePool.reset();
}

const VulkanSemaphorePool &VulkanRenderFrame::getSemaphorePool() const {
    return semaphorePool;
}

const VulkanFencePool &VulkanRenderFrame::getFencePool() const {
    return fencePool;
}

const VulkanRenderTarget &VulkanRenderFrame::getRenderTarget() const {
    return *renderTarget;
}

void VulkanRenderFrame::updateRenderTarget(std::unique_ptr<VulkanRenderTarget> &&newRenderTarget) {
    renderTarget = std::move(newRenderTarget);
}

VulkanCommandBuffer &VulkanRenderFrame::getCommandBufer() {
    commandPool->requestCommandBuffer();
}

vk::Fence VulkanRenderFrame::requestFence() {
    return fencePool.requestFence();
}

vk::Semaphore VulkanRenderFrame::requestSemaphore() {
    return semaphorePool.requestSemaphore();
}

} // namespace Elements
