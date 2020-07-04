#pragma once

#include "Core/Application.h"
#include "Core/System.h"
#include "WindowSystem/WindowMessage.h"
#include "WindowSystem/WindowSystem.h"

namespace Elements {

class RenderSystem : public System {
  public:
    RenderSystem();
    ~RenderSystem();

    void postMessage(Message *msg);
    void handleMessage(Message *msg);
};
} // namespace Elements
