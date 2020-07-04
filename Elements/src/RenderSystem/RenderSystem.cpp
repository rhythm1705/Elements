#include "RenderSystem.h"

#include <vulkan/vulkan.hpp>

namespace Elements {
RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {}

void RenderSystem::postMessage(Message *msg) { getBus()->addMessage(msg); }

void RenderSystem::handleMessage(Message *msg) {

}
} // namespace Elements