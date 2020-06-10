#include "elmtpch.h"

#include "MessageBus.h"

namespace Elements {

    void MessageBus::addMessage(Message* msg) {
        messageQueue.push(msg);
    }

    Message* MessageBus::getMessage() {
        return messageQueue.front();
    }

    void MessageBus::popMessage() {
        delete messageQueue.front();
        messageQueue.pop();
    }

    bool MessageBus::isEmpty() {
        return messageQueue.empty();
    }

    MessageBus::MessageBus() {
    }

    MessageBus::~MessageBus() {
        while (!messageQueue.empty()) {
            messageQueue.pop();
        }
    }

}