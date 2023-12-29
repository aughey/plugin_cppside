#include <iostream>
#include "plugin.h"

class DynamicPlugin : public plugin::IPlugin
{
public:
    DynamicPlugin()
    {
        std::cout << "DynamicPlugin::DynamicPlugin()" << std::endl;
    }
    virtual ~DynamicPlugin() {}
    virtual void initialize()
    {
        std::cout << "DynamicPlugin::initialize()" << std::endl;
    }
    virtual void OnFrame(plugin::IInterface *interface)
    {
        std::cout << "DynamicPlugin::OnFrame()" << std::endl;
        std::cout << "Name: " << interface->getName() << std::endl;
        std::cout << "Position: (" << interface->getPositionX() << ", " << interface->getPositionY() << ", " << interface->getPositionZ() << ")" << std::endl;
        std::cout << "Frame: " << interface->getFrame() << std::endl;
    }
    virtual void OnExit()
    {
        std::cout << "DynamicPlugin::OnExit()" << std::endl;
    }
};

extern "C"
{
    void initialize()
    {
        std::cout << "dynamic_plugin initialize()" << std::endl;
    }
    plugin::IPlugin *create()
    {
        return new DynamicPlugin();
    }
}