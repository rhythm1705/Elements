#include "elmtpch.h"
#include "KeyInputMessage.h"

namespace Elements {
    KeyPressedMessage::KeyPressedMessage(System* sender, std::any data) : Message{ sender, data } {
        KeyPressedMessage::type = MessageType::KeyDown;
    }
    KeyCode KeyPressedMessage::getKeyCode() {
        return std::any_cast<std::pair<KeyCode, int>>(data).first;
    }

    int KeyPressedMessage::getRepeatCount() {
        return std::any_cast<std::pair<KeyCode, int>>(data).second;
    }



    KeyReleasedMessage::KeyReleasedMessage(System* sender, std::any data) : Message{ sender, data } {
        KeyReleasedMessage::type = MessageType::KeyUp;
    }

    KeyCode KeyReleasedMessage::getKeyCode() {
        return std::any_cast<KeyCode>(data);
    }

}


