#pragma once

#include "elmtpch.h"


namespace Elements {

    class System;

    enum class MessageType {
        None = 0,

        // Test System
        TextInput,

        // Keyboard Input
        KeyDown,
        KeyUp,

        // Window
        WindowClose, 
        WindowResize, 
        WindowFocus, 
        WindowLostFocus, 
        WindowMoved,
    };

    class Message {
    public:
        MessageType getType() {
            return type;
        }
        std::any getData() {
            return data;
        }
        Message(System* sender, std::any data) : sender(sender), data(data) {
            type = MessageType::None;
        }
        Message(System* sender, MessageType type, std::any data) : sender(sender), type(type), data(data) {}
        ~Message();

    protected:
        MessageType type;
        std::any data;
        System* sender;
    };
}  // namespace Elements