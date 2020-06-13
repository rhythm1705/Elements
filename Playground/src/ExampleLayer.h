#pragma once

#include <Elements.h>

class ExampleLayer : public Elements::Layer {
 public:
  ExampleLayer() : Layer("Example"){};

  void onUpdate() override { ELMT_INFO("Example Layer updated!"); }

  void handleMessage(Elements::Message* msg) override { ELMT_INFO("Message received!"); }
};
