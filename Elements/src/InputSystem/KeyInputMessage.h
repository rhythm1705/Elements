#pragma once

#include "InputSystem/Keys.h"
#include "MessageSystem/Message.h"

namespace Elements {

class KeyDownMessage : public Message {
 public:
  KeyDownMessage(System* sender, std::any data) : Message{sender, data} {
    type = MessageType::KeyDown;
  }
  KeyCode getKeyCode() {
    return std::any_cast<std::pair<KeyCode, int>>(data).first;
  }
  int getRepeatCount() {
    return std::any_cast<std::pair<KeyCode, int>>(data).second;
  };
};

class KeyUpMessage : public Message {
 public:
  KeyUpMessage(System* sender, std::any data) : Message{sender, data} {
    type = MessageType::KeyUp;
  }
  KeyCode getKeyCode() { return std::any_cast<KeyCode>(data); }
};
}  // namespace Elements
