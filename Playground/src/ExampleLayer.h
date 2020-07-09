#pragma once

#include <Elements.h>

class ExampleLayer : public Elements::Layer {
  public:
    ExampleLayer() : Layer("Example"){};

    void onUpdate() override {
        // ELMT_INFO("Example Layer updated!");
        auto bus = Elements::MessageBus::getBus();
        auto msg = bus->peek();
        if (msg->getType() == Elements::MessageType::KeyDown) {
            ELMT_INFO("Key Pressed");
        } else if (msg->getType() == Elements::MessageType::MouseButtonDown) {
            ELMT_INFO("Mouse Pressed");
        }
    }

    void handleMessage(Elements::Message *msg) override {}
};
