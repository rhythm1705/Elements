#include "elmtpch.h"
#include "Window.h"
#include "WindowMessage.h"

namespace Elements {

    static uint8_t GLFWWindowCount = 0;

    Elements::WindowSystem::WindowSystem(const WindowProps& props) {
        init(props);
    }

    Elements::WindowSystem::~WindowSystem() {
        shutdown();
    }

    void Elements::WindowSystem::onUpdate() {
        glfwPollEvents();
    }

    unsigned int Elements::WindowSystem::getHeight() {
        return 0;
    }

    unsigned int Elements::WindowSystem::getWidth() {
        return 0;
    }

    void WindowSystem::postWindowResizeMessage(WindowResizeMessage* msg) {
        Message* winRszMsg = msg;
        bus->addMessage(winRszMsg);
    }

    void WindowSystem::postWindowCloseMessage(WindowCloseMessage* msg) {
        Message* winClsMsg = msg;
        bus->addMessage(winClsMsg);
    }

    void WindowSystem::init(const WindowProps& props) {
        data.title = props.title;
        data.width = props.width;
        data.height = props.height;

        // Assign functions into data to be used inside lambda callbacks for GLFW.
        data.closeWindow = std::bind(&WindowSystem::postWindowCloseMessage, this, std::placeholders::_1);
        data.resizeWindow = std::bind(&WindowSystem::postWindowResizeMessage, this, std::placeholders::_1);

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
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeMessage* msg = new WindowResizeMessage(NULL, std::pair<unsigned int, unsigned int>(width, height));
            data.resizeWindow(msg);
            });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            WindowCloseMessage* msg =  new WindowCloseMessage(NULL, NULL);
            data.closeWindow(msg);
            });
    }

    void Elements::WindowSystem::shutdown() {
        glfwDestroyWindow(window);
        --GLFWWindowCount;

        if (GLFWWindowCount == 0) {
            glfwTerminate();
        }
    }

}

