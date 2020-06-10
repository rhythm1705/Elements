#pragma once

#include "Core.h"

#ifdef ELMT_PLATFORM_WINDOWS

extern Elements::Application* Elements::CreateApplication();

int main() {
    Elements::Log::init();
    ELMT_CORE_INFO("Welcome to Elements!");
    auto app = Elements::CreateApplication();
    app->run();
    delete app;
}

#endif