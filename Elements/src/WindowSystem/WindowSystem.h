#pragma once

#include "Core/System.h"
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
    WindowSystem(const WindowProps &props = WindowProps());
    ~WindowSystem();

    void postMessage(Message *msg);
    void handleMessage(Message *msg);

    void onUpdate();
    void onClose();
    void onResize(WindowResizeMessage *msg);

    unsigned int getHeight();
    unsigned int getWidth();

    GLFWwindow *getWindowPtr() { return window; }

    bool isRunning() { return running; }
    bool isMinimized() { return minimized; }

  private:
    void init(const WindowProps &props);
    void shutdown();

    GLFWwindow *window;
    WindowProps data;

    bool running;
    bool minimized;
};

} // namespace Elements
