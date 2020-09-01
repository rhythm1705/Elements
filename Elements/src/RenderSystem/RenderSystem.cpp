#include "RenderSystem.h"

#include "VulkanRenderer.h"

namespace Elements {

void RenderSystem::startUp() {
    VulkanRenderer::init();
}

void RenderSystem::shutDown() {
}

void RenderSystem::onUpdate() {
}


} // namespace Elements
