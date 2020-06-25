/* The bus that connects all the engine systems. A better way might be to use a linked list to
 * prevent resizing of queue. An immediate queue where the message's receiver is known for quicker
 * messaging might also be implemented. Uses a lot of dynamic allocations currently. */

#pragma once

#include "Message.h"

namespace Elements {

class MessageBus {
  public:
    std::queue<Message *> messageQueue;
    void addMessage(Message *msg);
    Message *getMessage();
    void popMessage();
    bool isEmpty();
    MessageBus();
    ~MessageBus();
};

} // namespace Elements