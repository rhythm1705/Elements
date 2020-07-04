/* Engine system for handling user input. */

#pragma once

#include "Core/System.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Elements {

class Input {
  public:
    bool isKeyPressed(KeyCode key);
    bool isMousePressed(MouseCode button);
    std::pair<float, float> getMousePosition();
    float getMouseXPosition();
    float getMouseYPosition();
};

} // namespace Elements
