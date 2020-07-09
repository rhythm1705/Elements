#pragma once

#include "Messaging/Message.h"

namespace Elements {

class WindowResizeMessage : public Message {
  public:
    WindowResizeMessage(std::any data) : Message{ data } { type = MessageType::WindowResize; }
    unsigned int getHeight() {
        return std::any_cast<std::pair<unsigned int, unsigned int>>(data).second;
    }
    unsigned int getWidth() {
        return std::any_cast<std::pair<unsigned int, unsigned int>>(data).first;
    };
};

class WindowCloseMessage : public Message {
  public:
    WindowCloseMessage(std::any data) : Message{ NULL } { type = MessageType::WindowClose; }
};
} // namespace Elements
