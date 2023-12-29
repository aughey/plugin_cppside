#include <iostream>
#include "plugin.h"
#include "c_interface.h"

// define the call-in interface
void interface_shutdown(plugin::IInterface *i)
{
    i->shutdown();
}
const char *interface_get_name(plugin::IInterface *i)
{
    return i->getName().c_str();
}

uint64_t interface_get_frame(plugin::IInterface *i)
{
    return i->getFrame();
}
double interface_get_position_x(plugin::IInterface *i)
{
    return i->getPositionX();
}
double interface_get_position_y(plugin::IInterface *i)
{
    return i->getPositionY();
}
double interface_get_position_z(plugin::IInterface *i)
{
    return i->getPositionZ();
}