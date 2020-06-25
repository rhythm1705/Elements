/* The entrypoint of the engine. */

#pragma once

#include "Core.h"
#include "System.h"

#ifdef ELMT_PLATFORM_WINDOWS

extern Elements::Application *Elements::CreateApplication();

int main() {
    Elements::Log::init();
    ELMT_CORE_INFO("Welcome to Elements!");
    Elements::System system;
    system.createBus();
    auto app = Elements::CreateApplication();
    app->run(system.getBus());
    delete app;
    system.deleteBus();
}

#endif
