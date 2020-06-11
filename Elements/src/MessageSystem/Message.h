#pragma once

#include "elmtpch.h"

namespace Elements {

class System;

enum class MessageType {
  None = 0,

  // Keyboard Input
  KeyDown,
  KeyUp,
  KeyType,

  // Window
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMove,
};

class Message {
 public:
  MessageType getType() { return type; }
  std::any getData() { return data; }
  Message(std::any data) : data(data) { type = MessageType::None; }
  Message(MessageType type, std::any data) : type(type), data(data) {}
  ~Message() {}

 protected:
  MessageType type;
  std::any data;
};
}  // namespace Elements