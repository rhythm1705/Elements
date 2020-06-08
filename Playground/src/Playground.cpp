#include <Elements.h>

class Playground : public Elements::Application {

public:
    Playground() {}

    ~Playground() {}

};

Elements::Application* Elements::CreateApplication() {
    return new Playground();
}