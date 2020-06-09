#pragma once

#include "elmtpch.h"

#include <GLFW/glfw3.h>

namespace Elements {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "Elements Game Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : title(title), width(width), height(height) {
        }
    };

    class Window {
    public:
        Window(const WindowProps& props);
        ~Window();
        void onUpdate();
        unsigned int getHeight();
        unsigned int getWidth();

    private:
        void init(const WindowProps& props);
        void shutdown();
        GLFWwindow* window;
        WindowProps data;
    };
}

