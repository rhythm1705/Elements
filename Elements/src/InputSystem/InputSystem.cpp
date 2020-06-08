#include "elmtpch.h"

#include "InputSystem.h"

namespace Elements {
    void InputSystem::handleMessage() {
        Message* msg = bus->getMessage();
        if (msg->type == MessageType::TextInput) {
            std::cout << "MESSAGE RECEIVED!" << std::endl;
        }
    }
}