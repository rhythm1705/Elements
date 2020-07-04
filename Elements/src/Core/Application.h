/* The main class that boots up the systems and runs the engine. */

#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "System.h"
#include "WindowSystem/Input/Input.h"
#include "WindowSystem/Input/KeyInputMessage.h"
#include "WindowSystem/WindowSystem.h"

namespace Elements {

class Application {
  public:
    Application();
    virtual ~Application();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *layer);

    void run(MessageBus *bus);
    WindowSystem &getWindow() { return *windowSystem; }
    static Application &get() { return *instance; }

  private:
    static Application *instance;
    LayerStack layerStack;
    std::unique_ptr<WindowSystem> windowSystem;
};

Application *CreateApplication();

} // namespace Elements
