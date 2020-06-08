#pragma once

#include "Message.h"

//#include <vector>
#include <queue>

namespace Elements {

    class MessageBus {

    public:
        //std::vector<System> systems;
        std::queue<Message*> messageQueue;
        void postMessage(Message* msg);
        Message* getMessage();
        void popMessage();
        MessageBus();
        ~MessageBus();
    };
}