#pragma once

#include <Elements.h>

class ExampleLayer : public Elements::Layer {
  public:
    ExampleLayer() : Layer("Example"){};

    void onUpdate() override {
        // ELMT_INFO("Example Layer updated!");
    }

    void handleMessage(Elements::Message *msg) override {
        if (msg->getType() == Elements::MessageType::KeyDown) {
            ELMT_INFO("Key Pressed");
        } else if (msg->getType() == Elements::MessageType::MouseButtonDown) {
            ELMT_INFO("Mouse Pressed");
        }
    }
};
