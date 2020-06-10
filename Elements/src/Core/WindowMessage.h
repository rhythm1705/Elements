#pragma once

#include "MessageSystem/Message.h"

namespace Elements {

class WindowResizeMessage : public Message {
 public:
  WindowResizeMessage(System* sender, std::any data) : Message{sender, data} {
    type = MessageType::WindowResize;
  }
  unsigned int getHeight() {
    return std::any_cast<std::pair<unsigned int, unsigned int>>(data).second;
  }
  unsigned int getWidth() {
    return std::any_cast<std::pair<unsigned int, unsigned int>>(data).first;
  };
};

class WindowCloseMessage : public Message {
 public:
  WindowCloseMessage(System* sender, std::any data) : Message{sender, NULL} {
    type = MessageType::WindowClose;
  }
};
}  // namespace Elements
