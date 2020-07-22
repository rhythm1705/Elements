#pragma once

#include "Core/System.h"

#include <vulkan/vulkan.hpp>

namespace Elements {

class RenderSystem : public System {
  public:
    void startUp() override;
    void shutDown() override;
    void onUpdate() override;

  private:
};

} // namespace Elements
