#include "Application.h"

#include "InputSystem/InputSystem.h"
#include "MessageSystem/MessageBus.h"
#include "InputSystem/KeyInputMessage.h"

namespace Elements {

Application::Application() {
  bus = new MessageBus();
  window = std::unique_ptr<WindowSystem>(new WindowSystem(WindowProps()));
}

Application::~Application() {}

void Application::run() {
  while (running) {
    if (!bus->isEmpty()) {
      handleMessage();
      bus->popMessage();
    }
    window->onUpdate();
  }
}

void Application::close() { running = false; }

void Application::handleMessage() {
  Message* msg = bus->getMessage();
  if (msg->getType() == MessageType::WindowClose) {
    ELMT_CORE_INFO("Closing Window");
    Application::onWindowClose();
  } else if (msg->getType() == MessageType::WindowResize) {
    ELMT_CORE_INFO("Resizing Window");
    WindowResizeMessage* rszMsg = (WindowResizeMessage*)msg;
    Application::onWindowResize(rszMsg);
  } else if (msg->getType() == MessageType::KeyDown) {
    ELMT_CORE_INFO("{0}", ((KeyDownMessage*)msg)->getKeyCode());
  }
}

void Application::onWindowClose() { running = false; }

void Application::onWindowResize(WindowResizeMessage* msg) {
  if (msg->getWidth() == 0 || msg->getHeight() == 0) {
    minimized = true;
  }
  minimized = false;
}
}  // namespace Elements