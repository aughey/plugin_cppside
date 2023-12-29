#include <iostream>
#include "local_plugin.h"

LocalPlugin::LocalPlugin() {
    std::cout << "LocalPlugin::LocalPlugin()" << std::endl;
}

void LocalPlugin::initialize() {
    std::cout << "LocalPlugin::initialize()" << std::endl;
}

void LocalPlugin::OnFrame(plugin::IInterface *interface) {
    std::cout << "LocalPlugin::OnFrame()" << std::endl;
    std::cout << "Name: " << interface->getName() << std::endl;
    std::cout << "Position: (" << interface->getPositionX() << ", " << interface->getPositionY() << ", " << interface->getPositionZ() << ")" << std::endl;
}

void LocalPlugin::OnExit() {
    std::cout << "LocalPlugin::OnExit()" << std::endl;
}