#include "System.h"

namespace Elements {

    MessageBus* System::bus;

    void System::handleMessage() {
    }

    void System::sendMessage(MessageType type, std::any data) {
        Message* msg = new Message(this, type, data);
        bus->postMessage(msg);
    }

    System::System() {
    }

    System::~System() {
    }

}