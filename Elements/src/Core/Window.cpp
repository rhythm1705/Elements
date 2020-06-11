#include "Window.h"

#include "InputSystem/KeyInputMessage.h"
#include "WindowMessage.h"

namespace Elements {

static uint8_t GLFWWindowCount = 0;

Elements::WindowSystem::WindowSystem(const WindowProps& props) { init(props); }

Elements::WindowSystem::~WindowSystem() { shutdown(); }

void Elements::WindowSystem::onUpdate() { glfwPollEvents(); }

unsigned int Elements::WindowSystem::getHeight() { return 0; }

unsigned int Elements::WindowSystem::getWidth() { return 0; }

void WindowSystem::postMessage(Message* msg) {
  // Message* winRszMsg = msg;
  bus->addMessage(msg);
}

// void WindowSystem::postWindowCloseMessage(WindowCloseMessage* msg) {
//  Message* winClsMsg = msg;
//  bus->addMessage(winClsMsg);
//}

void WindowSystem::init(const WindowProps& props) {
  data.title = props.title;
  data.width = props.width;
  data.height = props.height;

  // Assign functions into data to be used inside lambda callbacks for GLFW.

  data.windowMessage =
      std::bind(&WindowSystem::postMessage, this, std::placeholders::_1);

  ELMT_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width,
                 props.height);

  if (GLFWWindowCount == 0) {
    glfwInit();
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow((int)data.width, (int)data.height,
                            data.title.c_str(), nullptr, nullptr);
  ++GLFWWindowCount;

  glfwSetWindowUserPointer(window, &data);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(
      window, [](GLFWwindow* window, int width, int height) {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;
        WindowResizeMessage* msg = new WindowResizeMessage(
            std::pair<unsigned int, unsigned int>(width, height));
        data.windowMessage(msg);
      });

  glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
    WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
    WindowCloseMessage* msg = new WindowCloseMessage(NULL);
    data.windowMessage(msg);
  });

  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
    WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

    switch (action) {
      case GLFW_PRESS: {
        KeyDownMessage* msg = new KeyDownMessage(
            std::pair<KeyCode, int>(static_cast<KeyCode>(key), 0));
        data.windowMessage(msg);
        break;
      }
      case GLFW_RELEASE: {
        KeyUpMessage* msg = new KeyUpMessage(static_cast<KeyCode>(key));
        data.windowMessage(msg);
        break;
      }
      case GLFW_REPEAT: {
        KeyDownMessage* msg = new KeyDownMessage(
            std::pair<KeyCode, int>(static_cast<KeyCode>(key), 1));
        data.windowMessage(msg);
        break;
      }
    }
  });
}

void Elements::WindowSystem::shutdown() {
  glfwDestroyWindow(window);
  --GLFWWindowCount;

  if (GLFWWindowCount == 0) {
    glfwTerminate();
  }
}

}  // namespace Elements
