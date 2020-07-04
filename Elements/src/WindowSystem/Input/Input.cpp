#include "Input.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Elements {

bool Input::isKeyPressed(KeyCode key) {
    auto window = Application::get().getWindow().getWindowPtr();
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMousePressed(MouseCode button) {
    auto window = Application::get().getWindow().getWindowPtr();
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::getMousePosition() {
    auto window = Application::get().getWindow().getWindowPtr();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

float Input::getMouseXPosition() {
    auto [x, y] = getMousePosition();
    return x;
}

float Input::getMouseYPosition() {
    auto [x, y] = getMousePosition();
    return y;
}

} // namespace Elements