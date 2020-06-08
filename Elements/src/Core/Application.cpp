#include "elmtpch.h"

#include "Application.h"

#include "MessageSystem/MessageBus.h"
#include "InputSystem/InputSystem.h"

#include <stdio.h>

namespace Elements {

    Application::Application() {}

    Application::~Application() {}

    void Application::Run() {
        printf("Hello World");
        MessageBus* bus = new MessageBus();
        System* system = new System();
        system->bus = bus;
        system->sendMessage(MessageType::TextInput, NULL);
        InputSystem* input = new InputSystem();
        input->handleMessage();
        // while (true);
    }
} // namespace Elements