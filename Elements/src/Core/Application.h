#pragma once

#include "Core.h"
#include "Window.h"

namespace Elements {

    class  Application {

    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> window;

    };

    Application* CreateApplication();

} // namespace Elements
