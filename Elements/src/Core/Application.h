/* The main class that boots up the systems and runs the engine. */

#pragma once

#include "Core.h"
#include "InputSystem/InputSystem.h"
#include "InputSystem/KeyInputMessage.h"
#include "LayerStack.h"
#include "System.h"
#include "WindowSystem/Window.h"
#include "WindowSystem/WindowMessage.h"

namespace Elements {

class Application {
 public:
  Application();
  virtual ~Application();

  void pushLayer(Layer* layer);
  void pushOverlay(Layer* layer);

  void run(MessageBus* bus);
  WindowSystem& getWindow() { return *window; }
  static Application& get() { return *instance; }

 private:
  static Application* instance;
  LayerStack layerStack;
  std::unique_ptr<WindowSystem> window;
  std::unique_ptr<InputSystem> input;
};

Application* CreateApplication();

}  // namespace Elements
