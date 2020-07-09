#include "Application.h"

#include "Messaging/MessageBus.h"

namespace Elements {

Application *Application::instance = nullptr;

Application::Application() {
    instance = this;
    windowSystem = std::make_unique<WindowSystem>();
    renderSystem = std::make_unique<RenderSystem>();
}

Application::~Application() {
    // Shut down all systems
    renderSystem->shutDown();
    windowSystem->shutDown();
}

void Application::pushLayer(Layer *layer) {
    layerStack.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
    layerStack.pushOverlay(layer);
    layer->onAttach();
}

void Application::run() {
    // Start up all systems
    windowSystem->startUp();
    renderSystem->startUp();

    // Get the message bus
    auto bus = MessageBus::getBus();

    while (windowSystem->isRunning()) {
        if (!windowSystem->isMinimized()) {
            while (!bus->isEmpty()) {
                for (auto layer : layerStack) {
                    layer->onUpdate();
                }
                bus->popMessage();
            }
        }
        windowSystem->onUpdate();
        renderSystem->onUpdate();
    }
}

} // namespace Elements
