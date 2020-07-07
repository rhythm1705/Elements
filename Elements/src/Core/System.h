/* An interface for different engine systems. */

// TODO: Add  startUp, shutDown and process message methods. Handle message gets the latest message
// from bus, if handled then return, else process the message.

#pragma once

#include "MessageSystem/Message.h"
#include "MessageSystem/MessageBus.h"

namespace Elements {

class System {
  public:
    System();
    ~System();

    void createBus();
    MessageBus *getBus() { return bus; }
    void deleteBus();

    virtual void handleMessage();
    void postMessage(MessageType type, std::any data);

  private:
    static MessageBus *bus;
};

} // namespace Elements
