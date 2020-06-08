#pragma once

#include "MessageSystem/Message.h"
#include "MessageSystem/MessageBus.h"

namespace Elements {

    class System {
    public:
        static MessageBus* bus;
        virtual void handleMessage();
        void sendMessage(MessageType type, std::any data);
        System();
        ~System();
    };

}
