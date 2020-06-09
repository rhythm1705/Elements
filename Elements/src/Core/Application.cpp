#include "elmtpch.h"

#include "Application.h"

#include "MessageSystem/MessageBus.h"
#include "InputSystem/InputSystem.h"

namespace Elements {

    Application::Application() {
        window = std::unique_ptr<Window>(new Window(WindowProps()));
    }

    Application::~Application() {}

    void Application::Run() {
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
        while (true);
    }
} // namespace Elements