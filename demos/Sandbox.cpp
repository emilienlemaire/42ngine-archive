//
// Created by Emilien Lemaire on 14/03/2020.
//

#include "../42ngine.h"

class Sandbox : public ftn::Application {
public:
    Sandbox() = default;
    ~Sandbox() override = default;
};
ftn::Application* ftn::createApplication() {
    return new Sandbox();
}
