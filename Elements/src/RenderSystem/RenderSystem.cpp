#include "RenderSystem.h"

#include "Core/Application.h"
#include "Vulkan/VulkanCommandBuffers.h"
#include "Vulkan/VulkanCommandPool.h"
#include "Vulkan/VulkanDevice.h"
#include "Vulkan/VulkanImageView.h"
#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanSwapChain.h"
#include "Vulkan/VulkanValidationLayers.h"

namespace Elements {

void RenderSystem::startUp() {
    auto window = Application::get().getWindow().getWindowPtr();
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        data.framebufferResized = true;
    });
}

void RenderSystem::shutDown() {
    
}

void RenderSystem::onUpdate() {
    
}


} // namespace Elements
