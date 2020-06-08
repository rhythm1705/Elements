#pragma once

#include "Core.h"

namespace Elements {

    class  Application {

    public:
        Application();
        virtual ~Application();

        void Run();

    };

    Application* CreateApplication();

} // namespace Elements
