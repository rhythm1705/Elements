#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanCommandBuffer;

class VulkanQueue {
  public:
    VulkanQueue(VulkanDevice &device, uint32_t familyIndex, vk::Bool32 canPresent);
    ~VulkanQueue();

    const VulkanDevice &getDevice() const;

    vk::Queue getHandle() const;
    uint32_t getFamilyIndex() const;
    vk::Bool32 supportPresent() const;

    void submit(const std::vector<vk::SubmitInfo> &submitInfos, vk::Fence fence) const;
    void submit(const VulkanCommandBuffer &commandBuffer, vk::Fence fence) const;
    void present(const vk::PresentInfoKHR &presentInfo) const;
    void waitIdle() const;

  private:
    VulkanDevice &device;

    vk::Queue handle;

    uint32_t familyIndex{ 0 };
    vk::Bool32 canPresent{ VK_FALSE };
};

} // namespace Elements
