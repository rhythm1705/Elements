#pragma once

#include "Message.h"

namespace Elements {

    // A better way might be to use a linked list to prevent resizing of queue.
    class MessageBus {

    public:
        //std::vector<System> systems;
        std::queue<Message*> messageQueue;
        void addMessage(Message* msg);
        Message* getMessage();
        void popMessage();
        bool isEmpty();
        MessageBus();
        ~MessageBus();
    };
}