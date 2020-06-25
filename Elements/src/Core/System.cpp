#include "System.h"

namespace Elements {

MessageBus *System::bus;

System::System() {}

System::~System() {}

void System::createBus() { bus = new MessageBus(); }

void System::deleteBus() { delete bus; }

void System::handleMessage() {}

void System::postMessage(MessageType type, std::any data) {
    Message *msg = new Message(type, data);
    bus->addMessage(msg);
}

} // namespace Elements