#include "elmtpch.h"

#include "InputSystem.h"

namespace Elements {
    void InputSystem::handleMessage() {
        Message* msg = bus->getMessage();
        if (msg->getType() == MessageType::TextInput) {
            std::cout << "MESSAGE RECEIVED: " << std::any_cast<std::string>(msg->getData()) << std::endl;
        }
    }
}