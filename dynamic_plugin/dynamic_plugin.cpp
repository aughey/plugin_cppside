#include <iostream>
#include "plugin.h"
#include "c_interface.h"
#include "adapter.h"

class DynamicPlugin : public plugin::IPlugin
{
public:
    DynamicPlugin()
    {
        //std::cout << "DynamicPlugin::DynamicPlugin()" << std::endl;
        plugin_constructor(this);
    }
    virtual ~DynamicPlugin()
    {
        plugin_destructor(this);
    }
    virtual void initialize()
    {
        //std::cout << "DynamicPlugin::initialize()" << std::endl;
        plugin_on_initialize(this);
    }
    virtual void OnFrame(plugin::IInterface *interface)
    {
        plugin_on_frame(this, interface);
        // std::cout << "DynamicPlugin::OnFrame()" << std::endl;
        // std::cout << "Name: " << interface->getName() << std::endl;
        // std::cout << "Position: (" << interface->getPositionX() << ", " << interface->getPositionY() << ", " << interface->getPositionZ() << ")" << std::endl;
        // std::cout << "Frame: " << interface->getFrame() << std::endl;
    }
    virtual void OnExit()
    {
        // std::cout << "DynamicPlugin::OnExit()" << std::endl;
        plugin_on_exit(this);
    }
};

extern "C"
{
    void initialize()
    {
        //std::cout << "dynamic_plugin initialize()" << std::endl;
        rust_initialize();
    }
    plugin::IPlugin *create()
    {
        return new DynamicPlugin();
    }
}