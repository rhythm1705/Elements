#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanPipelineLayout;
class VulkanRenderPass;

struct VertexInputState {
    std::vector<vk::VertexInputBindingDescription> bindings;
    std::vector<vk::VertexInputAttributeDescription> attributes;
};

struct InputAssemblyState {
    vk::PrimitiveTopology topology{ vk::PrimitiveTopology::eTriangleList };
    vk::Bool32 primitiveRestartEnable{ VK_FALSE };
};

struct RasterizationState {
    vk::Bool32 depthClampEnable{ VK_FALSE };
    vk::Bool32 rasterizerDiscardEnable{ VK_FALSE };
    vk::PolygonMode polygonMode{ vk::PolygonMode::eFill };
    vk::CullModeFlags cullMode{ vk::CullModeFlagBits::eBack };
    vk::FrontFace frontFace{ vk::FrontFace::eClockwise };
    vk::Bool32 depthBiasEnable{ VK_FALSE };
};

struct ViewportState {
    uint32_t viewportCount{ 1 };
    uint32_t scissorCount{ 1 };
    vk::Viewport viewport;
    vk::Rect2D scissors;
};

struct MultisampleState {
    vk::SampleCountFlagBits rasterizationSamples{ vk::SampleCountFlagBits::e1 };
    vk::Bool32 sampleShadingEnable{ VK_FALSE };
    float minSampleShading{ 1.0f };
    vk::SampleMask sampleMask{ 0 };
    vk::Bool32 alphaToCoverageEnable{ VK_FALSE };
    vk::Bool32 alphaToOneEnable{ VK_FALSE };
};

struct StencilOpState {
    vk::StencilOp failOp{ vk::StencilOp::eReplace };
    vk::StencilOp passOp{ vk::StencilOp::eReplace };
    vk::StencilOp depthFailOp{ vk::StencilOp::eReplace };
    vk::CompareOp compareOp{ vk::CompareOp::eNever };
};

struct DepthStencilState {
    vk::Bool32 depthTestEnable{ VK_TRUE };
    vk::Bool32 depthWriteEnable{ VK_TRUE };
    // Note: Using Reversed depth-buffer for increased precision, so Greater depth values are kept
    vk::CompareOp depthCompareOp{ vk::CompareOp::eGreater };
    vk::Bool32 depthBoundsTestEnable{ VK_FALSE };
    vk::Bool32 stencilTestEnable{ VK_FALSE };
    StencilOpState front{};
    StencilOpState back{};
};

struct ColorBlendAttachmentState {
    vk::Bool32 blendEnable{ VK_FALSE };
    vk::BlendFactor srcColorBlendFactor{ vk::BlendFactor::eOne };
    vk::BlendFactor dstColorBlendFactor{ vk::BlendFactor::eZero };
    vk::BlendOp colorBlendOp{ vk::BlendOp::eAdd };
    vk::BlendFactor srcAlphaBlendFactor{ vk::BlendFactor::eOne };
    vk::BlendFactor dstAlphaBlendFactor{ vk::BlendFactor::eZero };
    vk::BlendOp alphaBlendOp{ vk::BlendOp::eAdd };
    vk::ColorComponentFlags colorWriteMask{ vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
                                            | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA };
};

struct ColorBlendState {
    vk::Bool32 logicOpEnable{ VK_FALSE };
    vk::LogicOp logicOp{ vk::LogicOp::eClear };
    std::vector<ColorBlendAttachmentState> attachments;
};

class VulkanPipelineState {
  public:
    void reset();

    // Setters
    void setPipelineLayout(VulkanPipelineLayout &pipelineLayout);
    void setRenderPass(const VulkanRenderPass &renderPass);
    void setVertexInputState(const VertexInputState &vertexInputState);
    void setInputAssemblyState(const InputAssemblyState &inputAssemblyState);
    void setRasterizationState(const RasterizationState &rasterizationState);
    void setViewportState(const ViewportState &viewportState);
    void setMultisampleState(const MultisampleState &multisampleState);
    void setStencilOpState(const StencilOpState &stencilOpState);
    void setDepthStenciState(const DepthStencilState &depthStencilState);
    void setColorBlendState(const ColorBlendState &colorBlendState);

    // Getters
    const VulkanPipelineLayout &getPipelineLayout() const;
    const VulkanRenderPass *getRenderPass() const;
    const VertexInputState &getVertexInputState() const;
    const InputAssemblyState &getInputAssemblyState() const;
    const RasterizationState &getRasterizationState() const;
    const ViewportState &getViewportState() const;
    const MultisampleState &getMultisampleState() const;
    const StencilOpState &getStencilOpState() const;
    const DepthStencilState &getDepthStenciState() const;
    const ColorBlendState &getColorBlendState() const;

  private:
    VulkanPipelineLayout *pipelineLayout;
    const VulkanRenderPass *renderPass;
    VertexInputState vertexInputState;
    InputAssemblyState inputAssemblyState;
    RasterizationState rasterizationState;
    ViewportState viewportState;
    MultisampleState multisampleState;
    StencilOpState stencilOpState;
    DepthStencilState depthStencilState;
    ColorBlendState colorBlendState;
};

} // namespace Elements
