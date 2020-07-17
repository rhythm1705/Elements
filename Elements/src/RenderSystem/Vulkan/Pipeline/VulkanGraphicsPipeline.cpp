#include "VulkanGraphicsPipeline.h"

#include "RenderSystem/Vulkan/RenderPass/VulkanStandardRenderPass.h"
#include "RenderSystem/Vulkan/VulkanDevice.h"
#include "RenderSystem/Vulkan/VulkanShaderManager.h"

namespace Elements {

VulkanGraphicsPipeline::VulkanGraphicsPipeline(const char *vertexShader,
                                               const char *fragmentShader,
                                               const vk::Extent2D &swapChainExtent) {
    vk::ShaderModule vertShaderModule = VulkanShaderManager::getInstance()->getShaderModule(vertexShader);
    vk::ShaderModule fragShaderModule = VulkanShaderManager::getInstance()->getShaderModule(fragmentShader);
    vk::PipelineShaderStageCreateInfo vertShaderStageInfo(
      vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eVertex, vertShaderModule, "main");
    vk::PipelineShaderStageCreateInfo fragShaderStageInfo(
      vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eFragment, fragShaderModule, "main");
    vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    vk::PipelineVertexInputStateCreateInfo vertexInputInfo(
      vk::PipelineVertexInputStateCreateFlags(), 0, nullptr, 0, nullptr);

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly(
      vk::PipelineInputAssemblyStateCreateFlags(), vk::PrimitiveTopology::eTriangleList, false);

    vk::Viewport viewport(0.0f, 0.0f, (float)swapChainExtent.width, (float)swapChainExtent.height, 0.0f, 1.0f);
    vk::Rect2D scissors({ 0, 0 }, swapChainExtent);
    vk::PipelineViewportStateCreateInfo viewportState(
      vk::PipelineViewportStateCreateFlags(), 1, &viewport, 1, &scissors);

    vk::PipelineRasterizationStateCreateInfo rasterizer(
      vk::PipelineRasterizationStateCreateFlags(), VK_FALSE, VK_FALSE, vk::PolygonMode::eFill,
      vk::CullModeFlagBits::eBack, vk::FrontFace::eClockwise, VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f);

    vk::PipelineMultisampleStateCreateInfo multisampling(vk::PipelineMultisampleStateCreateFlags(),
                                                         vk::SampleCountFlagBits::e1, VK_FALSE,
                                                         1.0f, nullptr, VK_FALSE, VK_FALSE);
    vk::PipelineColorBlendAttachmentState colorBlendAttachment(
      VK_FALSE, vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd,
      vk::BlendFactor::eOne, vk::BlendFactor::eZero, vk::BlendOp::eAdd,
      vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
        | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

    vk::PipelineColorBlendStateCreateInfo colorBlending(vk::PipelineColorBlendStateCreateFlags(), VK_FALSE,
                                                        vk::LogicOp::eCopy, 1, &colorBlendAttachment,
                                                        { 0.0f, 0.0f, 0.0f, 0.0f });

    vk::DynamicState dynamicStates[] = { vk::DynamicState::eViewport, vk::DynamicState::eLineWidth };
    vk::PipelineDynamicStateCreateInfo dynamicState(vk::PipelineDynamicStateCreateFlags(), 2, dynamicStates);

    vk::PipelineLayoutCreateInfo pipelineLayoutInfo(vk::PipelineLayoutCreateFlags(), 0, nullptr, 0, nullptr);
    if (VulkanDevice::getInstance()->getVulkanDevice().createPipelineLayout(&pipelineLayoutInfo, nullptr, &pipelineLayout)
        != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create vulkan pipeline layout!");
    }

    vk::GraphicsPipelineCreateInfo pipelineInfo(
      vk::PipelineCreateFlags(), 2, shaderStages, &vertexInputInfo, &inputAssembly, nullptr,
      &viewportState, &rasterizer, &multisampling, nullptr, &colorBlending, nullptr, pipelineLayout,
      VulkanStandardRenderPass::getInstance()->getRenderPass(), 0, nullptr, -1);
    if (VulkanDevice::getInstance()->getVulkanDevice().createGraphicsPipelines(
          nullptr, 1, &pipelineInfo, nullptr, &handle)
        != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to create graphics pipeline!");
    }
    VulkanShaderManager::getInstance()->cleanUpShaders();
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline() {
    VulkanDevice::getInstance()->getVulkanDevice().destroyPipeline(handle);
    VulkanDevice::getInstance()->getVulkanDevice().destroyPipelineLayout(pipelineLayout);
}

vk::Pipeline VulkanGraphicsPipeline::getPipeline() { return handle; }

vk::PipelineLayout VulkanGraphicsPipeline::getPipelineLayout() { return pipelineLayout; }
} // namespace Elements