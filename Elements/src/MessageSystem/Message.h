#pragma once

#include "elmtpch.h"


namespace Elements {

    class System;

    enum class MessageType {
        None = 0,

        // Test System
        TextInput,

        // Keyboard Input
        KeyUp,
        KeyDown,

        // Window
        WindowOpen,
        WindowClosed,
    };

    class Message {
    public:
        MessageType type;
        std::any data;
        System* sender;
        Message(System* sender, std::any data);
        Message(System* sender, MessageType type, std::any data);
        ~Message();
    };
}  // namespace Elements