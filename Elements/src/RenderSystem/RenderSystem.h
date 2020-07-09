#pragma once

#include "Core/System.h"

namespace Elements {

class RenderSystem : public System {
  public:
    void startUp() override;
    void shutDown() override;
    void onUpdate() override;

  private:
    void init();


};
} // namespace Elements
