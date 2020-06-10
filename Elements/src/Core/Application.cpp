#include "elmtpch.h"

#include "Application.h"

#include "MessageSystem/MessageBus.h"
#include "InputSystem/InputSystem.h"

namespace Elements {

    Application::Application() {
        bus = new MessageBus();
        window = std::unique_ptr<WindowSystem>(new WindowSystem(WindowProps()));
    }

    Application::~Application() {}

    void Application::run() {
        while (running) {
            if (!bus->isEmpty()) {
                ELMT_CORE_INFO("Dispatching Message.");
                handleMessage();
                bus->popMessage();
            }
            window->onUpdate();
        }
    }
    void Application::close() {
        running = false;
    }
    void Application::handleMessage() {
        ELMT_CORE_INFO("Received Message.");
        Message* msg = bus->getMessage();
        if (msg->getType() == MessageType::WindowClose) {
            Application::onWindowClose();
        }
        else if (msg->getType() == MessageType::WindowResize) {
            ELMT_CORE_INFO("Resizing Window");
            WindowResizeMessage* rszMsg = (WindowResizeMessage*) msg;
            Application::onWindowResize(rszMsg);
        }
    }
    void Application::onWindowClose() {
        running = false;
    }
    void Application::onWindowResize(WindowResizeMessage* msg) {
        if (msg->getWidth() == 0 || msg->getHeight() == 0) {
            minimized = true;
        }

        minimized = false;
    }
} // namespace Elements