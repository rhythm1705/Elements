#pragma once

#include "Core/System.h"

#include <vulkan/vulkan.hpp>

namespace Elements {

class RenderSystem : public System {
  public:
    void startUp() override;
    void shutDown() override;
    void onUpdate() override;

  private:
    void init();
    void recreateSwapChain();
    void cleanUpSwapchain();

    size_t currentFrame = 0;

    std::vector<vk::Semaphore> imageAvailableSemaphores;
    std::vector<vk::Semaphore> renderFinishedSemaphores;
    std::vector<vk::Fence> inFlightFences;
    std::vector<vk::Fence> imagesInFlight;
    vk::SwapchainKHR swapChain;
    std::vector<vk::ImageView> swapChainImageViews;
    std::vector<vk::Framebuffer> framebuffers;
    std::vector<vk::CommandBuffer> commandBuffers;
    vk::CommandPool commandPool;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;
    vk::Pipeline graphicsPipeline;
    vk::PipelineLayout pipelineLayout;
};

} // namespace Elements
