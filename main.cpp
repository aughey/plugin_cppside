#include <iostream>
#include <vector>
#include "plugin.h"
#include "local_plugin.h"
#include "fake_interface.h"
#include "load_shared.h"
#include <unistd.h>

typedef std::vector<plugin::IPlugin *> pluginlist;
typedef std::vector<plugin::IPlugin *>::iterator pluginlistiterator;

int main(int argc, char *argv[])
{
    // first arg is the path to the shared object to load
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <soPath>" << std::endl;
        return 1;
    }

    // Path to the shared object
    const char *soPath = argv[1];

    // Load the shared object and create the plugin
    plugin::IPlugin *plugin = shared::load_so_and_create_plugin(soPath);
    if (!plugin)
    {
        std::cerr << "Failed to load plugin" << std::endl;
        return 1;
    }

    // Our list of plugins to run in a simplified executive
    pluginlist plugins;
    plugins.push_back(plugin);

    // Create a fake interface to pass to the plugins.  This defines simple
    // methods that the plugins can call to get information about the
    // environment.
    FakeInterface fakeInterface;

    // run initialize on all plugins
    for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
    {
        plugin::IPlugin *plugin = *it;
        plugin->initialize();
    }

    // Our main executive loop, run until the plugins tell us to shutdown
    while (fakeInterface.inShutdown() == false)
    {
        // For each plugin, run it's OnFrame method
        for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
        {
            plugin::IPlugin *plugin = *it;
            plugin->OnFrame(&fakeInterface);
        }
        // sleep 1 second
        sleep(1);
        // Move to the next frame
        fakeInterface.incrementFrame();
    }

    // tell all teh plugins to exist and delete them
    for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
    {
        plugin::IPlugin *plugin = *it;
        plugin->OnExit();
        delete plugin;
    }
    plugins.clear();

    return 0;
}
