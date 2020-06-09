#pragma once

#include "MessageSystem/Message.h"
#include "InputSystem/Keys.h"

namespace Elements {

    class KeyPressedMessage : public Message {
    public:
        KeyPressedMessage(System* sender, std::any data);
        KeyCode getKeyCode();
        int getRepeatCount();
        

    };

    class KeyReleasedMessage : public Message {
    public:
        KeyReleasedMessage(System* sender, std::any data);
        KeyCode getKeyCode();

    };
}


