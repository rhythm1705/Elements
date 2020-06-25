#include "Window.h"

#include "InputSystem/KeyInputMessage.h"
#include "InputSystem/MouseInputMessage.h"
#include "WindowMessage.h"

namespace Elements {

static uint8_t GLFWWindowCount = 0;

Elements::WindowSystem::WindowSystem(const WindowProps &props) { init(props); }

Elements::WindowSystem::~WindowSystem() { shutdown(); }

void Elements::WindowSystem::onUpdate() { glfwPollEvents(); }

unsigned int Elements::WindowSystem::getHeight() { return 0; }

unsigned int Elements::WindowSystem::getWidth() { return 0; }

void WindowSystem::postMessage(Message *msg) { getBus()->addMessage(msg); }

void WindowSystem::handleMessage(Message *msg) {
    if (msg->getType() == MessageType::WindowClose) {
        ELMT_CORE_INFO("Closing Window");
        WindowSystem::onClose();
    } else if (msg->getType() == MessageType::WindowResize) {
        // ELMT_CORE_INFO("Resizing Window");
        WindowResizeMessage *rszMsg = (WindowResizeMessage *)msg;
        WindowSystem::onResize(rszMsg);
    }
}

void WindowSystem::onClose() { running = false; }

void WindowSystem::onResize(WindowResizeMessage *msg) {
    if (msg->getWidth() == 0 || msg->getHeight() == 0) {
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
        WindowResizeMessage *msg
          = new WindowResizeMessage(std::pair<unsigned int, unsigned int>(width, height));
        data.windowMessage(msg);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
        WindowProps &data = *(WindowProps *)glfwGetWindowUserPointer(window);
        WindowCloseMessage *msg = new WindowCloseMessage(NULL);
        data.windowMessage(msg);
    });

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

void Elements::WindowSystem::shutdown() {
    glfwDestroyWindow(window);
    --GLFWWindowCount;

    if (GLFWWindowCount == 0) {
        glfwTerminate();
    }
}

} // namespace Elements
