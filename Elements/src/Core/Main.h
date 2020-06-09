#pragma once

#include "Core.h"

#ifdef ELMT_PLATFORM_WINDOWS

extern Elements::Application* Elements::CreateApplication();

int main() {
    Elements::Log::init();
    ELMT_INFO("Welcome to Elements!");
    auto app = Elements::CreateApplication();
    app->Run();
    delete app;
}

#endif