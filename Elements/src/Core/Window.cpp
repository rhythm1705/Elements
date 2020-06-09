#include "elmtpch.h"
#include "Core.h"
#include "Window.h"

namespace Elements {

    static uint8_t GLFWWindowCount = 0;

    Elements::Window::Window(const WindowProps& props) {
        init(props);
    }

    Elements::Window::~Window() {
        shutdown();
    }

    void Elements::Window::onUpdate() {
        glfwPollEvents();
    }

    unsigned int Elements::Window::getHeight() {
        return 0;
    }

    unsigned int Elements::Window::getWidth() {
        return 0;
    }

    void Elements::Window::init(const WindowProps& props) {
        //ELMT_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (GLFWWindowCount == 0) {
            glfwInit();
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
        ++GLFWWindowCount;
    }

    void Elements::Window::shutdown() {
        glfwDestroyWindow(window);
        --GLFWWindowCount;

        if (GLFWWindowCount == 0) {
            glfwTerminate();
        }
    }

}

