#include "Application.h"

#include "Messaging/MessageBus.h"

namespace Elements {

Application *Application::instance = nullptr;

Application::Application() {
    instance = this;
    windowSystem = std::make_unique<WindowSystem>();
}

Application::~Application() {}

void Application::pushLayer(Layer *layer) {
    layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
    layerStack.pushOverlay(layer);
    layer->onAttach();
}

void Application::run(MessageBus *bus) {
    while (windowSystem->isRunning()) {
        if (!bus->isEmpty()) {
            Message *msg = bus->getMessage();
            windowSystem->handleMessage(msg);
            for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
                if (msg->isHandled()) break;
                (*it)->handleMessage(msg);
            }
            bus->popMessage();
        }
        if (!windowSystem->isMinimized()) {
            for (auto layer : layerStack) {
                layer->onUpdate();
            }
        }
        windowSystem->onUpdate();
    }
}

} // namespace Elements
