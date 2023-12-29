#pragma once

namespace plugin
{
    class IInterface;
    class IPlugin;
}

extern "C"
{
    void rust_initialize();
    void plugin_constructor(plugin::IPlugin *);
    void plugin_destructor(plugin::IPlugin *);
    void plugin_on_initialize(plugin::IPlugin *);
    void plugin_on_frame(plugin::IPlugin *, plugin::IInterface *);
    void plugin_on_exit(plugin::IPlugin *);
}