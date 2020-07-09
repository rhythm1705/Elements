/* The bus that connects all the engine systems. A better way might be to use a linked list to
 * prevent resizing of queue. An immediate queue where the message's receiver is known for quicker
 * messaging might also be implemented. Uses a lot of dynamic allocations currently. */

// TODO: Make it a singleton class.

#pragma once

#include "Message.h"

namespace Elements {

class MessageBus {
  public:
    static MessageBus *getBus();

    void addMessage(Message *msg);
    void popMessage();

    Message *peek();

    bool isEmpty();

  private:
    MessageBus();
    ~MessageBus();

    static MessageBus *instance;

    std::queue<Message *> messageQueue;
};

} // namespace Elements