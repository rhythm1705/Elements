#pragma once

#include "InputSystem/Keys.h"
#include "MessageSystem/Message.h"

namespace Elements {

class KeyDownMessage : public Message {
 public:
  KeyDownMessage(std::any data) : Message{data} { type = MessageType::KeyDown; }
  KeyCode getKeyCode() {
    return std::any_cast<std::pair<KeyCode, int>>(data).first;
  }
  int getRepeatCount() {
    return std::any_cast<std::pair<KeyCode, int>>(data).second;
  };
};

class KeyUpMessage : public Message {
 public:
  KeyUpMessage(std::any data) : Message{data} { type = MessageType::KeyUp; }
  KeyCode getKeyCode() { return std::any_cast<KeyCode>(data); }
};

class KeyTypeMessage : public Message {
 public:
  KeyTypeMessage(std::any data) : Message{data} { type = MessageType::KeyType; }
  KeyCode getKeyCode() { return std::any_cast<KeyCode>(data); }
};
}  // namespace Elements
