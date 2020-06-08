#include "MessageBus.h"

namespace Elements {

    void MessageBus::postMessage(Message* msg) {
        messageQueue.push(msg);
    }

    Message* MessageBus::getMessage() {
        return messageQueue.front();
    }

    void MessageBus::popMessage() {
        messageQueue.pop();
    }

    MessageBus::MessageBus() {
    }

    MessageBus::~MessageBus() {
        while (!messageQueue.empty()) {
            messageQueue.pop();
        }
    }

}