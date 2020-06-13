#pragma once

#include "Core/System.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Elements {

class InputSystem : System {
 public:
  bool isKeyPressed(KeyCode key);
  bool isMousePressed(MouseCode button);
  std::pair<float, float> getMousePosition();
  float getMouseXPosition();
  float getMouseYPosition();
  void handleMessage();
};

}  // namespace Elements
