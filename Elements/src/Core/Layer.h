/* Class to separate different levels of surface in an application. */

#pragma once

#include "MessageSystem/Message.h"

namespace Elements {

class Layer {
  public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onImGuiRender() {}
    virtual void handleMessage(Message *message) {}

    const std::string &GetName() const { return debugName; }

  protected:
    std::string debugName;
};

} // namespace Elements