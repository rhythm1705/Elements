#include <Elements.h>

#include "ExampleLayer.h"

class Playground : public Elements::Application {
 public:
  Playground() { pushLayer(new ExampleLayer()); }

  ~Playground() {}
};

Elements::Application* Elements::CreateApplication() {
  return new Playground();
}