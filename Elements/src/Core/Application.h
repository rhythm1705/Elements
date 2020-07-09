/* The main class that boots up the systems and runs the engine. */

#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "WindowSystem/WindowSystem.h"
#include "RenderSystem/RenderSystem.h"

namespace Elements {

class Application {
  public:
    Application();
    virtual ~Application();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *layer);

    void run();
    WindowSystem &getWindow() { return *windowSystem; }
    static Application &get() { return *instance; }

  private:
    static Application *instance;
    LayerStack layerStack;

    std::unique_ptr<WindowSystem> windowSystem;
    std::unique_ptr<RenderSystem> renderSystem;
};

Application *CreateApplication();

} // namespace Elements
