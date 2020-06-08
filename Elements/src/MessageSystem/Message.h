#pragma once

//#include "Core/System.h"

#include <any>
#include <string>

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

    struct Message {
        MessageType type;
        std::any data;
        System* sender;
        Message(System* sender, MessageType type, std::any data);
        ~Message();
    };
}  // namespace Elements