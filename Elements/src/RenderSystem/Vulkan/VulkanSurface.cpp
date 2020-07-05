#include "VulkanSurface.h"

#include "Core/Application.h"
#include "RenderSystem/Vulkan/VulkanInstance.h"

#include <GLFW/glfw3.h>

namespace Elements {
VulkanSurface *vulkanSurface = nullptr;

VulkanSurface *VulkanSurface::getInstance() {
    if (!vulkanSurface) {
        vulkanSurface = new VulkanSurface();
        vulkanSurface->init();
    }
    return vulkanSurface;
}

void VulkanSurface::init() {
    auto window = Application::get().getWindow().getWindowPtr();
    if (glfwCreateWindowSurface(VulkanInstance::getInstance()->getVulkanInstance(), window, nullptr,
                                reinterpret_cast<VkSurfaceKHR *>(&surface))
        != VK_SUCCESS) {
        ELMT_CORE_ERROR("Failed to create vulkan window surface!");
    }
}

void VulkanSurface::destroy() {
    VulkanInstance::getInstance()->getVulkanInstance().destroySurfaceKHR(surface);
}

} // namespace Elements