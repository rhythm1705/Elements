#pragma once

#include "Core/System.h"
#include "Messaging/Message.h"
#include "WindowSystem/WindowMessage.h"

#include <GLFW/glfw3.h>

namespace Elements {

struct WindowProps {
    std::string title;
    unsigned int width;
    unsigned int height;
    std::function<void(Message *)> windowMessage;

    WindowProps(const std::string &title = "Elements Game Engine", unsigned int width = 1280, unsigned int height = 720)
    : title(title), width(width), height(height) {}
};

class WindowSystem : public System {
  public:
    void startUp() override;
    void shutDown() override;
    void onUpdate() override;

    void onClose();
    void onResize(int width, int height);

    unsigned int getHeight();
    unsigned int getWidth();

    GLFWwindow *getWindowPtr() { return window; }

    bool isRunning() { return running; }
    bool isMinimized() { return minimized; }

  private:
    void init(const WindowProps &props = WindowProps());

    GLFWwindow *window;
    WindowProps data;

    bool running;
    bool minimized;
};

} // namespace Elements
