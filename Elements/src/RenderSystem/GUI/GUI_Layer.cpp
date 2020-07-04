#include "GUI_Layer.h"

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_vulkan.h>
#include <imgui.h>
#include <vulkan/vulkan.hpp>

namespace Elements {
GUI_Layer::GUI_Layer() : Layer("GUI Layer") {}

GUI_Layer::~GUI_Layer() {}

void GUI_Layer::onAttach() {}

void GUI_Layer::onDetach() {}

void GUI_Layer::onUpdate() {}

void GUI_Layer::handleMessage(Message *message) {}

} // namespace Elements
