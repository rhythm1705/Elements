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

void Application::pushLayer(Layer* layer) {
  layerStack.pushLayer(layer);
  layer->onAttach();
}

void Application::pushOverlay(Layer* layer) {
  layerStack.pushOverlay(layer);
  layer->onAttach();
}

void Application::run(MessageBus* bus) {
  while (window->isRunning()) {
    if (!bus->isEmpty()) {
      Message* msg = bus->getMessage();
      window->handleMessage(msg);
      input->handleMessage();
      for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
        if (msg->isHandled()) break;
        (*it)->handleMessage(msg);
      }
      bus->popMessage();
    }
    if (!window->isMinimized()) {
      for (auto layer : layerStack) {
        layer->onUpdate();
      }
    }
    window->onUpdate();
  }
}

}  // namespace Elements
