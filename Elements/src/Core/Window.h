#pragma once

#include "elmtpch.h"

#include "System.h"
#include "WindowMessage.h"

#include <GLFW/glfw3.h>

namespace Elements {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;
        std::function<void(WindowResizeMessage*)> resizeWindow;
        std::function<void(WindowCloseMessage*)> closeWindow;


        WindowProps(const std::string& title = "Elements Game Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : title(title), width(width), height(height) {
        }
    };

    class WindowSystem : System {
    public:
        WindowSystem(const WindowProps& props);
        ~WindowSystem();
        void onUpdate();
        unsigned int getHeight();
        unsigned int getWidth();
        void postWindowResizeMessage(WindowResizeMessage* msg);
        void postWindowCloseMessage(WindowCloseMessage* msg);

    private:
        void init(const WindowProps& props);
        void shutdown();
        GLFWwindow* window;
        WindowProps data;
    };
}

