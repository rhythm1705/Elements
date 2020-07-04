#pragma once

#include "Core/Layer.h"

namespace Elements {

class GUI_Layer : public Layer {
  public:
    GUI_Layer();
    ~GUI_Layer();

    void onAttach();
    void onDetach();

    void onUpdate();
    void handleMessage(Message *message);
};

} // namespace Elements
