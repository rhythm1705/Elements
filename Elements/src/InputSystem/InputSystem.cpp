#include "InputSystem.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Elements {

bool InputSystem::isKeyPressed(KeyCode key) {
    auto window = Application::get().getWindow().getWindow();
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool InputSystem::isMousePressed(MouseCode button) {
    auto window = Application::get().getWindow().getWindow();
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

std::pair<float, float> InputSystem::getMousePosition() {
    auto window = Application::get().getWindow().getWindow();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

float InputSystem::getMouseXPosition() {
    auto [x, y] = getMousePosition();
    return x;
}

float InputSystem::getMouseYPosition() {
    auto [x, y] = getMousePosition();
    return y;
}

void InputSystem::handleMessage() {}

} // namespace Elements