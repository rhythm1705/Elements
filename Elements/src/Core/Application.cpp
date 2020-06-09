#include "elmtpch.h"

#include "Application.h"

#include "MessageSystem/MessageBus.h"
#include "InputSystem/InputSystem.h"

#include <stdio.h>

namespace Elements {

    Application::Application() {}

    Application::~Application() {}

    void Application::Run() {
        printf("Hello World\n");
        MessageBus* bus = new MessageBus();
        System* system = new System();
        system->bus = bus;
        std::string out = "HELLO WORLD!";
        system->sendMessage(MessageType::TextInput, out);
        system->sendMessage(MessageType::TextInput, std::string("100"));
        InputSystem* input = new InputSystem();
        input->handleMessage();
        bus->popMessage();
        input->handleMessage();
        // while (true);
    }
} // namespace Elements