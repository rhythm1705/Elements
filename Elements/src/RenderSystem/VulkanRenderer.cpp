#include "VulkanRenderer.h"

#include "Core/Application.h"
#include "Vulkan/Pipeline/VulkanPipelineLayout.h"
#include "Vulkan/Pipeline/VulkanPipelineState.h"
#include "Vulkan/VulkanRenderFrame.h"
#include "Vulkan/VulkanRenderTarget.h"
#include "Vulkan/VulkanShaderModule.h"

namespace Elements {

vk::SurfaceKHR VulkanRenderer::surface;
std::unique_ptr<VulkanInstance> VulkanRenderer::instance;
std::unique_ptr<VulkanDevice> VulkanRenderer::device;
std::unique_ptr<VulkanRenderContext> VulkanRenderer::context;
std::unique_ptr<VulkanRenderPass> VulkanRenderer::renderPass;
std::unique_ptr<VulkanGraphicsPipeline> VulkanRenderer::pipeline;


void VulkanRenderer::init() {
    auto window = Application::get().getWindow().getWindowPtr();
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        data.framebufferResized = true;
    });

    instance = std::make_unique<VulkanInstance>("Elements Renderer",
                                                VK_MAKE_VERSION(1, 0, 0),
                                                "Elements",
                                                VK_MAKE_VERSION(1, 0, 0));

    surface = instance->getSurface();

    device = std::make_unique<VulkanDevice>(instance->getHandle(), surface);

    context = std::make_unique<VulkanRenderContext>(*device,
                                                    surface,
                                                    Application::get().getWindow().getWidth(),
                                                    Application::get().getWindow().getHeight());

    context->prepare();

    std::vector<Attachment> attachments;
    attachments.push_back(context->getFormat());
    std::vector<LoadStoreInfo> infos;
    infos.push_back(LoadStoreInfo());
    std::vector<SubpassInfo> subpasses;
    subpasses.push_back(SubpassInfo());
    renderPass = std::make_unique<VulkanRenderPass>(*device, attachments, infos, subpasses);

    std::vector<VulkanShaderModule *> shaderModules;
    shaderModules.push_back(
      new VulkanShaderModule("assets/shaders/vert.spv", vk::ShaderStageFlagBits::eVertex, "main"));
    shaderModules.push_back(
      new VulkanShaderModule("assets/shaders/frag.spv", vk::ShaderStageFlagBits::eFragment, "main"));
    VulkanPipelineLayout layout(*device, shaderModules);

    VulkanPipelineState pipelineState;
    pipelineState.setPipelineLayout(layout);
    vk::Viewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)context->getSwapchain().getswapChainExtent().width;
    viewport.height = (float)context->getSwapchain().getswapChainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vk::Rect2D scissor;
    scissor.offset = { 0, 0 };
    scissor.extent = context->getSwapchain().getswapChainExtent();
    ViewportState state;
    state.viewport = viewport;
    state.scissors = scissor;
    pipelineState.setViewportState(state);
    pipelineState.setRenderPass(*renderPass);
    pipeline = std::make_unique<VulkanGraphicsPipeline>(*device, pipelineState);

    for (auto module : shaderModules) {
        delete module;
    }
    shaderModules.clear();

    device->createFramebuffers(context->getRenderFrames().back()->getRenderTarget(), *renderPass);
}

void VulkanRenderer::drawTriangle() {
}

void VulkanRenderer::update() {
}

void VulkanRenderer::resize(const uint32_t width, const uint32_t height) {
}

} // namespace Elements
