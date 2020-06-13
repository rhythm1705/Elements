#include "MessageBus.h"

namespace Elements {

void MessageBus::addMessage(Message* msg) { messageQueue.push(msg); }

Message* MessageBus::getMessage() { return messageQueue.front(); }

void MessageBus::popMessage() {
  //ELMT_CORE_INFO("{0}", messageQueue.front()->toString());
  delete messageQueue.front();
  messageQueue.pop();
}

bool MessageBus::isEmpty() { return messageQueue.empty(); }

MessageBus::MessageBus() {}

MessageBus::~MessageBus() {
  while (!messageQueue.empty()) {
    popMessage();
  }
}

}  // namespace Elements