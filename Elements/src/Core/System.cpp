#include "System.h"

namespace Elements {

MessageBus* System::bus;

void System::handleMessage() {}

void System::postMessage(MessageType type, std::any data) {
  Message* msg = new Message(type, data);
  bus->addMessage(msg);
}

System::System() {}

System::~System() {}

}  // namespace Elements