#include "WindowSystem.h"

#include "Core/Application.h"
#include "Messaging/MessageBus.h"
#include "WindowSystem/Input/KeyInputMessage.h"
#include "WindowSystem/Input/MouseInputMessage.h"

namespace Elements {

static uint8_t GLFWWindowCount = 0;

void Elements::WindowSystem::startUp() { init(); }

void Elements::WindowSystem::shutDown() {
    glfwDestroyWindow(window);
    --GLFWWindowCount;

    if (GLFWWindowCount == 0) {
        glfwTerminate();
    }
}

void Elements::WindowSystem::onUpdate() { glfwPollEvents(); }

unsigned int Elements::WindowSystem::getHeight() { return data.width; }

unsigned int Elements::WindowSystem::getWidth() { return data.height; }

void WindowSystem::onClose() { running = false; }

void WindowSystem::onResize(int width, int height) {
    if (width == 0 || height == 0) {
        minimized = true;
    }
    minimized = false;
}

void WindowSystem::init(const WindowProps &props) {
    data.title = props.title;
    data.width = props.width;
    data.height = props.height;

    // Assign message posting function into data to be used inside lambda callbacks for GLFW.
    data.windowMessage = std::bind(&WindowSystem::postMessage, this, std::placeholders::_1);

    ELMT_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (GLFWWindowCount == 0) {
        glfwInit();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow((int)data.width, (int)data.height, data.title.c_str(), nullptr, nullptr);
    ++GLFWWindowCount;

    glfwSetWindowUserPointer(window, &data);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;
        Application::get().getWindow().onResize(width, height);
    });

    glfwSetWindowCloseCallback(
      window, [](GLFWwindow *window) { Application::get().getWindow().onClose(); });

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
            KeyDownMessage *msg = new KeyDownMessage(std::pair<KeyCode, int>(static_cast<KeyCode>(key), 0));
            data.windowMessage(msg);
            break;
        }
        case GLFW_RELEASE: {
            KeyUpMessage *msg = new KeyUpMessage(static_cast<KeyCode>(key));
            data.windowMessage(msg);
            break;
        }
        case GLFW_REPEAT: {
            KeyDownMessage *msg = new KeyDownMessage(std::pair<KeyCode, int>(static_cast<KeyCode>(key), 1));
            data.windowMessage(msg);
            break;
        }
        }
    });

    glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int keycode) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        KeyTypeMessage *msg = new KeyTypeMessage(static_cast<KeyCode>(keycode));
        data.windowMessage(msg);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
            MouseButtonDownMessage *msg = new MouseButtonDownMessage(static_cast<MouseCode>(button));
            data.windowMessage(msg);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonUpMessage *msg = new MouseButtonUpMessage(static_cast<MouseCode>(button));
            data.windowMessage(msg);
            break;
        }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        MouseScrollMessage *msg
          = new MouseScrollMessage(std::pair<float, float>((float)xOffset, (float)yOffset));
        data.windowMessage(msg);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        MouseMoveMessage *msg = new MouseMoveMessage(std::pair<float, float>((float)xPos, (float)yPos));
        data.windowMessage(msg);
    });
}

void WindowSystem::postMessage(Message *message) {
    auto bus = MessageBus::getBus();
    bus->addMessage(message);
}

} // namespace Elements
