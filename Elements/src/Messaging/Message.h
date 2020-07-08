/* Class for creating message objects used to communicate between engine
 * systems. */

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

    // Mouse Input
    MouseMove,
    MouseScroll,
    MouseButtonDown,
    MouseButtonUp,

    // Window
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMove,
};

class Message {
  public:
    Message(std::any data) : data(data) { type = MessageType::None; }
    Message(MessageType type, std::any data) : type(type), data(data) {}
    ~Message() {}

    MessageType getType() { return type; }
    std::any getData() { return data; }

    std::string toString() {
        std::stringstream dataContents;
        dataContents << data.type().name();
        return dataContents.str();
    }

    bool isHandled() { return handled; }
    void markHandled() { handled = true; }

  protected:
    MessageType type;
    std::any data;
    bool handled = false;
};
} // namespace Elements