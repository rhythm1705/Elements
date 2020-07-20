#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanDevice;
class VulkanQueue;
class VulkanRenderFrame;
class VulkanSwapchain;
class VulkanCommandBuffer;

class VulkanRenderContext {
  public:
    VulkanRenderContext(VulkanDevice &device, vk::SurfaceKHR surface, uint32_t width, uint32_t height);
    ~VulkanRenderContext();

    VulkanDevice &getDevice();

    // Requests to set the present mode of the swapchain, must be called before prepare
    void requestPresentMode(const vk::PresentModeKHR presentMode);

    // Requests to set a specific image format for the swapchain
    void requestImageFormat(const vk::Format format);

    // Sets the order in which the swapchain prioritizes selecting its present mode
    void setPresentModePriority(const std::vector<vk::PresentModeKHR> &presentModePriorityList);

    // Sets the order in which the swapchain prioritizes selecting its surface format
    void setSurfaceFormatPriority(const std::vector<vk::SurfaceFormatKHR> &surfaceFormatPriorityList);

    // Prepares the RenderFrames for rendering
    void prepare();

    // Updates the swapchains extent, if a swapchain exists
    void updateSwapchain(const vk::Extent2D &extent);

    // Updates the swapchains image count, if a swapchain exists
    void updateSwapchain(const uint32_t imageCount);

    // Updates the swapchains image usage, if a swapchain exists
    void updateSwapchain(const std::set<vk::ImageUsageFlagBits> &imageUsageFlags);

    // Updates the swapchains extent and surface transform, if a swapchain exists
    void updateSwapchain(const vk::Extent2D &extent, const vk::SurfaceTransformFlagBitsKHR transform);

    // True if a valid swapchain exists in the RenderContext
    bool hasSwapchain();

    // Recreates the RenderFrames, called after every update
    void recreate();

    // Recreates the swapchain
    void recreateSwapchain();

    // Prepares the next available frame for rendering
    VulkanCommandBuffer &begin();

    // Submits the command buffer to the right queue
    void submit(VulkanCommandBuffer &commandBuffer);

    // beginFrame
    vk::Semaphore beginFrame();

    vk::Semaphore submit(const VulkanQueue &queue,
                         const VulkanCommandBuffer &commandBuffer,
                         vk::Semaphore waitSemaphore,
                         vk::PipelineStageFlags wait_pipelineStage);

    // Submits a command buffer related to a frame to a queue
    void submit(const VulkanQueue &queue, const VulkanCommandBuffer &commandBuffer);

    // Waits a frame to finish its rendering
    virtual void waitFrame();

    void endFrame(vk::Semaphore semaphore);

    // An error should be raised if the frame is not active.
    VulkanRenderFrame &getActiveFrame();

    // An error should be raised if the frame is not active.
    uint32_t getActiveFrameIndex();

    // An error should be raised if a frame is active.
    VulkanRenderFrame &getLastRenderedFrame();

    vk::Semaphore requestSemaphore();

    VulkanDevice &getDevice();

    // Returns the format that the RenderTargets are created with within the RenderContext
    vk::Format getFormat();

    VulkanSwapchain &getSwapchain();

    vk::Extent2D getSurface_extent() const;

    uint32_t getActiveFrameIndex() const;

    std::vector<std::unique_ptr<VulkanRenderFrame>> &getRenderFrames();

  private:
    VulkanDevice &device;

    vk::Extent2D surfaceExtent;

    std::vector<std::unique_ptr<VulkanRenderFrame>> frames;

    std::unique_ptr<VulkanSwapchain> swapchain;

    const VulkanQueue queue;
    vk::Semaphore acquiredSemaphore;

    /// Current active frame index
    uint32_t activeFrameIndex{ 0 };

    /// Whether a frame is active or not
    bool frameActive{ false };

    // A list of present modes in order of priority (vector[0] has high priority, vector[size-1] has
    // low priority)
    std::vector<vk::PresentModeKHR> presentModePriorityList
      = { vk::PresentModeKHR::eFifo, vk::PresentModeKHR::eMailbox };

    //// A list of surface formats in order of priority (vector[0] has high priority, vector[size-1]
    //// has low priority)
    // std::vector<vk::SurfaceFormatKHR> surfaceFormatPriorityList
    //  = { { VK_FORMAT_R8G8B8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR },
    //      { VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR },
    //      { VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR },
    //      { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR } };
};

} // namespace Elements
