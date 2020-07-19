#include "VulkanGraphicsPipeline.h"

#include "RenderSystem/Vulkan/VulkanDevice.h"
#include "RenderSystem/Vulkan/VulkanRenderPass.h"
#include "RenderSystem/Vulkan/VulkanShaderModule.h"
#include "VulkanPipelineLayout.h"
#include "VulkanPipelineState.h"

namespace Elements {

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VulkanDevice &device, VulkanPipelineState &pipelineState) :
device{ device }, pipelineState{ pipelineState } {
    // Create Shader modules and stages
    std::vector<vk::ShaderModule> shaderModules;
    std::vector<vk::PipelineShaderStageCreateInfo> stageCreateInfos;
    for (const VulkanShaderModule *shaderModule : pipelineState.getPipelineLayout().getShaderModules()) {
        vk::ShaderModuleCreateInfo shaderModuleInfo(
          vk::ShaderModuleCreateFlags(),
          shaderModule->getData().size(),
          reinterpret_cast<const uint32_t *>(shaderModule->getData().data()));
        vk::ShaderModule module;
        if (device.getHandle().createShaderModule(&shaderModuleInfo, nullptr, &module) != vk::Result::eSuccess) {
            ELMT_CORE_ERROR("Could not create shader module.");
        }
        vk::PipelineShaderStageCreateInfo shaderStageInfo(vk::PipelineShaderStageCreateFlags(),
                                                          shaderModule->getStage(),
                                                          module,
                                                          shaderModule->getEentryPoint().c_str());
        shaderModules.push_back(module);
        stageCreateInfos.push_back(shaderStageInfo);
    }

    // Assign state for the pipeline
    vk::PipelineVertexInputStateCreateInfo vertexInputInfo(vk::PipelineVertexInputStateCreateFlags(), 0, nullptr, 0, nullptr);

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly(vk::PipelineInputAssemblyStateCreateFlags(),
                                                           vk::PrimitiveTopology::eTriangleList,
                                                           false);


    vk::PipelineViewportStateCreateInfo viewportState(vk::PipelineViewportStateCreateFlags(),
                                                      pipelineState.getViewportState().viewportCount,
                                                      &pipelineState.getViewportState().viewport,
                                                      pipelineState.getViewportState().scissorCount,
                                                      &pipelineState.getViewportState().scissors);

    vk::PipelineRasterizationStateCreateInfo rasterizer(
      vk::PipelineRasterizationStateCreateFlags(),
      pipelineState.getRasterizationState().depthClampEnable,
      pipelineState.getRasterizationState().rasterizerDiscardEnable,
      pipelineState.getRasterizationState().polygonMode,
      pipelineState.getRasterizationState().cullMode,
      pipelineState.getRasterizationState().frontFace,
      pipelineState.getRasterizationState().depthBiasEnable,
      0.0f,
      0.0f,
      0.0f,
      1.0f);

    vk::PipelineMultisampleStateCreateInfo multisampling(
      vk::PipelineMultisampleStateCreateFlags(),
      pipelineState.getMultisampleState().rasterizationSamples,
      pipelineState.getMultisampleState().sampleShadingEnable,
      pipelineState.getMultisampleState().minSampleShading,
      nullptr,
      pipelineState.getMultisampleState().alphaToCoverageEnable,
      pipelineState.getMultisampleState().alphaToOneEnable);

    vk::PipelineColorBlendAttachmentState colorBlendAttachment(
      VK_FALSE,
      vk::BlendFactor::eOne,
      vk::BlendFactor::eZero,
      vk::BlendOp::eAdd,
      vk::BlendFactor::eOne,
      vk::BlendFactor::eZero,
      vk::BlendOp::eAdd,
      vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
        | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

    vk::PipelineColorBlendStateCreateInfo colorBlending(vk::PipelineColorBlendStateCreateFlags(),
                                                        VK_FALSE,
                                                        vk::LogicOp::eCopy,
                                                        1,
                                                        &colorBlendAttachment,
                                                        { 0.0f, 0.0f, 0.0f, 0.0f });

    vk::DynamicState dynamicStates[] = { vk::DynamicState::eViewport, vk::DynamicState::eLineWidth };
    vk::PipelineDynamicStateCreateInfo dynamicState(vk::PipelineDynamicStateCreateFlags(), 2, dynamicStates);

    // Create pipeline
    vk::GraphicsPipelineCreateInfo pipelineInfo(vk::PipelineCreateFlags(),
                                                stageCreateInfos.size(),
                                                stageCreateInfos.data(),
                                                &vertexInputInfo,
                                                &inputAssembly,
                                                nullptr,
                                                &viewportState,
                                                &rasterizer,
                                                &multisampling,
                                                nullptr,
                                                &colorBlending,
                                                nullptr,
                                                pipelineState.getPipelineLayout().getHandle(),
                                                pipelineState.getRenderPass()->getHandle(),
                                                0,
                                                nullptr,
                                                -1);
    if (device.getHandle().createGraphicsPipelines(nullptr, 1, &pipelineInfo, nullptr, &handle)
        != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("failed to create graphics pipeline!");
    }

    // Destroy shader modules
    for (auto shaderModule : shaderModules) {
        device.getHandle().destroyShaderModule(shaderModule);
    }
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline() {
    device.getHandle().destroyPipeline(handle);
}

vk::Pipeline VulkanGraphicsPipeline::getHandle() {
    return handle;
}

VulkanPipelineState VulkanGraphicsPipeline::getPipelineState() {
    return pipelineState;
}

} // namespace Elements