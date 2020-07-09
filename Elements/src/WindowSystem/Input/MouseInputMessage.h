/* Classes for Mouse input messages. */

#pragma once

#include "Messaging/Message.h"
#include "WindowSystem/Input/MouseCodes.h"

namespace Elements {

class MouseMoveMessage : public Message {
  public:
    MouseMoveMessage(std::any data) : Message{ data } { type = MessageType::MouseMove; }

    float getX() { return std::any_cast<std::pair<float, float>>(data).first; }

    float getY() { return std::any_cast<std::pair<float, float>>(data).second; }
};

class MouseScrollMessage : public Message {
  public:
    MouseScrollMessage(std::any data) : Message{ data } { type = MessageType::MouseScroll; }

    float getXOffset() { return std::any_cast<std::pair<float, float>>(data).first; }

    float getYOffset() { return std::any_cast<std::pair<float, float>>(data).second; }
};

class MouseButtonDownMessage : public Message {
  public:
    MouseButtonDownMessage(std::any data) : Message{ data } { type = MessageType::MouseButtonDown; }

    MouseCode getMouseCode() { return std::any_cast<MouseCode>(data); }
};

class MouseButtonUpMessage : public Message {
  public:
    MouseButtonUpMessage(std::any data) : Message{ data } { type = MessageType::MouseButtonUp; }

    MouseCode getMouseCode() { return std::any_cast<MouseCode>(data); }
};
} // namespace Elements