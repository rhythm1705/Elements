#pragma once

#include "Core.h"
#include "System.h"
#include "Window.h"
#include "WindowMessage.h"

namespace Elements {

    class  Application : System {

    public:
        Application();
        virtual ~Application();

        void run();
        void close();
        void handleMessage();
        void onWindowClose();
        void onWindowResize(WindowResizeMessage* msg);

    private:
        std::unique_ptr<WindowSystem> window;
        bool running = true;
        bool minimized = false;

    };

    Application* CreateApplication();

} // namespace Elements
