/* An interface for different engine systems. */

// TODO: Add  startUp, shutDown and process message methods. Handle message gets the latest message
// from bus, if handled then return, else process the message.

#pragma once

namespace Elements {

class System {
  public:
    System(){};
    ~System(){};
    virtual void startUp() = 0;
    virtual void shutDown() = 0;
    virtual void onUpdate() = 0;
};

} // namespace Elements
