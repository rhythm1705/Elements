#include "VulkanPipelineState.h"

#include "RenderSystem/Vulkan/VulkanRenderPass.h"
#include "VulkanPipelineLayout.h"

// Operators to compare structs

bool operator==(const Elements::ColorBlendAttachmentState &lhs, const Elements::ColorBlendAttachmentState &rhs) {
    return std::tie(lhs.alphaBlendOp,
                    lhs.blendEnable,
                    lhs.colorBlendOp,
                    lhs.colorWriteMask,
                    lhs.dstAlphaBlendFactor,
                    lhs.dstColorBlendFactor,
                    lhs.srcAlphaBlendFactor,
                    lhs.srcColorBlendFactor)
           == std::tie(rhs.alphaBlendOp,
                       rhs.blendEnable,
                       rhs.colorBlendOp,
                       rhs.colorWriteMask,
                       rhs.dstAlphaBlendFactor,
                       rhs.dstColorBlendFactor,
                       rhs.srcAlphaBlendFactor,
                       rhs.srcColorBlendFactor);
}

bool operator!=(const Elements::StencilOpState &lhs, const Elements::StencilOpState &rhs) {
    return std::tie(lhs.compareOp, lhs.depthFailOp, lhs.failOp, lhs.passOp)
           != std::tie(rhs.compareOp, rhs.depthFailOp, rhs.failOp, rhs.passOp);
}

bool operator!=(const Elements::VertexInputState &lhs, const Elements::VertexInputState &rhs) {
    return lhs.attributes != rhs.attributes || lhs.bindings != rhs.bindings;
}

bool operator!=(const Elements::InputAssemblyState &lhs, const Elements::InputAssemblyState &rhs) {
    return std::tie(lhs.primitiveRestartEnable, lhs.topology)
           != std::tie(rhs.primitiveRestartEnable, rhs.topology);
}

bool operator!=(const Elements::RasterizationState &lhs, const Elements::RasterizationState &rhs) {
    return std::tie(lhs.cullMode,
                    lhs.depthBiasEnable,
                    lhs.depthClampEnable,
                    lhs.frontFace,
                    lhs.frontFace,
                    lhs.polygonMode,
                    lhs.rasterizerDiscardEnable)
           != std::tie(rhs.cullMode,
                       rhs.depthBiasEnable,
                       rhs.depthClampEnable,
                       rhs.frontFace,
                       rhs.frontFace,
                       rhs.polygonMode,
                       rhs.rasterizerDiscardEnable);
}

bool operator!=(const Elements::ViewportState &lhs, const Elements::ViewportState &rhs) {
    return lhs.viewportCount != rhs.viewportCount || lhs.scissorCount != rhs.scissorCount;
}

bool operator!=(const Elements::MultisampleState &lhs, const Elements::MultisampleState &rhs) {
    return std::tie(lhs.alphaToCoverageEnable,
                    lhs.alphaToOneEnable,
                    lhs.minSampleShading,
                    lhs.rasterizationSamples,
                    lhs.sampleMask,
                    lhs.sampleShadingEnable)
           != std::tie(rhs.alphaToCoverageEnable,
                       rhs.alphaToOneEnable,
                       rhs.minSampleShading,
                       rhs.rasterizationSamples,
                       rhs.sampleMask,
                       rhs.sampleShadingEnable);
}

bool operator!=(const Elements::DepthStencilState &lhs, const Elements::DepthStencilState &rhs) {
    return std::tie(lhs.depthBoundsTestEnable,
                    lhs.depthCompareOp,
                    lhs.depthTestEnable,
                    lhs.depthWriteEnable,
                    lhs.stencilTestEnable)
             != std::tie(rhs.depthBoundsTestEnable,
                         rhs.depthCompareOp,
                         rhs.depthTestEnable,
                         rhs.depthWriteEnable,
                         rhs.stencilTestEnable)
           || lhs.back != rhs.back || lhs.front != rhs.front;
}

bool operator!=(const Elements::ColorBlendState &lhs, const Elements::ColorBlendState &rhs) {
    return std::tie(lhs.logicOp, lhs.logicOpEnable) != std::tie(rhs.logicOp, rhs.logicOpEnable)
           || lhs.attachments.size() != rhs.attachments.size()
           || !std::equal(lhs.attachments.begin(),
                          lhs.attachments.end(),
                          rhs.attachments.begin(),
                          [](const Elements::ColorBlendAttachmentState &lhs,
                             const Elements::ColorBlendAttachmentState &rhs) { return lhs == rhs; });
}

namespace Elements {

void VulkanPipelineState::reset() {
    pipelineLayout = nullptr;
    renderPass = nullptr;
    vertexInputState = {};
    inputAssemblyState = {};
    rasterizationState = {};
    viewportState = {};
    multisampleState = {};
    stencilOpState = {};
    depthStencilState = {};
    colorBlendState = {};
}

void VulkanPipelineState::setPipelineLayout(VulkanPipelineLayout &newPipelineLayout) {
    if (pipelineLayout) {
        if (pipelineLayout->getHandle() != newPipelineLayout.getHandle()) {
            pipelineLayout = &newPipelineLayout;
        }
    } else {
        pipelineLayout = &newPipelineLayout;
    }
}

void VulkanPipelineState::setRenderPass(const VulkanRenderPass &newRenderPass) {
    if (renderPass) {
        if (renderPass->getHandle() != newRenderPass.getHandle()) {
            renderPass = &newRenderPass;
        }
    } else {
        renderPass = &newRenderPass;
    }
}

void VulkanPipelineState::setVertexInputState(const VertexInputState &newVertexInputState) {
    if (vertexInputState != newVertexInputState) {
        vertexInputState = newVertexInputState;
    }
}

void VulkanPipelineState::setInputAssemblyState(const InputAssemblyState &newInputAssemblyState) {
    if (inputAssemblyState != newInputAssemblyState) {
        inputAssemblyState = newInputAssemblyState;
    }
}

void VulkanPipelineState::setRasterizationState(const RasterizationState &newRasterizationState) {
    if (rasterizationState != newRasterizationState) {
        rasterizationState = newRasterizationState;
    }
}

void VulkanPipelineState::setViewportState(const ViewportState &newViewportState) {
    // if (viewportState != newViewportState) {
    viewportState = newViewportState;
    //}
}

void VulkanPipelineState::setMultisampleState(const MultisampleState &newMultisampleState) {
    if (multisampleState != newMultisampleState) {
        multisampleState = newMultisampleState;
    }
}

void VulkanPipelineState::setStencilOpState(const StencilOpState &newStencilOpState) {
    if (stencilOpState != newStencilOpState) {
        stencilOpState = newStencilOpState;
    }
}

void VulkanPipelineState::setDepthStenciState(const DepthStencilState &newDepthStencilState) {
    if (depthStencilState != newDepthStencilState) {
        depthStencilState = newDepthStencilState;
    }
}

void VulkanPipelineState::setColorBlendState(const ColorBlendState &newColorBlendState) {
    if (colorBlendState != newColorBlendState) {
        colorBlendState = newColorBlendState;
    }
}

const VulkanPipelineLayout &VulkanPipelineState::getPipelineLayout() const {
    return *pipelineLayout;
}

const VulkanRenderPass *VulkanPipelineState::getRenderPass() const {
    return renderPass;
}

const VertexInputState &VulkanPipelineState::getVertexInputState() const {
    return vertexInputState;
}

const InputAssemblyState &VulkanPipelineState::getInputAssemblyState() const {
    return inputAssemblyState;
}

const RasterizationState &VulkanPipelineState::getRasterizationState() const {
    return rasterizationState;
}

const ViewportState &VulkanPipelineState::getViewportState() const {
    return viewportState;
}

const MultisampleState &VulkanPipelineState::getMultisampleState() const {
    return multisampleState;
}

const StencilOpState &VulkanPipelineState::getStencilOpState() const {
    return stencilOpState;
}

const DepthStencilState &VulkanPipelineState::getDepthStenciState() const {
    return depthStencilState;
}

const ColorBlendState &VulkanPipelineState::getColorBlendState() const {
    return colorBlendState;
}

} // namespace Elements
