//
// Created by Emilien Lemaire on 14/03/2020.
//

#pragma once

#include "../42ngine.h"

extern ftn::Application* ftn::createApplication();

int main(int argc, char** argv) {
    auto app = ftn::createApplication();
    app->run();
    delete  app;
}