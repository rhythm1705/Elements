#include "Application.h"

#include "MessageSystem/MessageBus.h"

namespace Elements {

Application* Application::instance = nullptr;

Application::Application() {
  instance = this; 
  window = std::make_unique<WindowSystem>();
  input = std::make_unique<InputSystem>();
}

Application::~Application() {}

void Application::run(MessageBus* bus) {
  while (window->isRunning()) {
    if (!bus->isEmpty()) {
      Message* msg = bus->getMessage();
      window->handleMessage(msg);
      bus->popMessage();
    }
    window->onUpdate();
  }
}

}  // namespace Elements
