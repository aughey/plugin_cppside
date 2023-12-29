#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "plugin.h"
#include "local_plugin.h"
#include <unistd.h>

typedef void (*InitializeFunc)();
typedef plugin::IPlugin *(*CreateFunc)();
typedef std::vector<plugin::IPlugin *> pluginlist;
typedef std::vector<plugin::IPlugin *>::iterator pluginlistiterator;

class FakeInterface : public plugin::IInterface
{
public:
    FakeInterface() : frame(0), name("FakeInterface") {}
    virtual ~FakeInterface() {}
    void incrementFrame()
    {
        frame++;
    }
    virtual const std::string &getName()
    {
        return name;
    }
    virtual ssize_t getFrame()
    {
        return frame;
    }
    virtual double getPositionX()
    {
        return 3.14;
    }
    virtual double getPositionY()
    {
        return 0.159;
    }
    virtual double getPositionZ()
    {
        return 0.265;
    }

protected:
    ssize_t frame;
    std::string name;
};

int main(int argc, char *argv[])
{
    // first arg is soPath
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <soPath>" << std::endl;
        return 1;
    }

    // Path to the shared object
    const char *soPath = argv[1];

    // Open the shared object
    void *handle = dlopen(soPath, RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // Reset errors
    dlerror();

    // Load the symbol
    InitializeFunc initialize = (InitializeFunc)dlsym(handle, "initialize");
    {
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cerr << "Cannot load symbol 'initialize': " << dlsym_error << '\n';
            dlclose(handle);
            return 1;
        }
    }

    CreateFunc create = (CreateFunc)dlsym(handle, "create");
    {
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cerr << "Cannot load symbol 'create': " << dlsym_error << '\n';
            dlclose(handle);
            return 1;
        }
    }

    // Use the function initialize();
    initialize();

    // Local our local plugin
    pluginlist plugins;
    //plugins.push_back(new LocalPlugin());
    plugins.push_back(create());
    FakeInterface fakeInterface;

    // run initialize on all plugins
    for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
    {
        plugin::IPlugin *plugin = *it;
        plugin->initialize();
    }

    while (true)
    {
        for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
        {
            plugin::IPlugin *plugin = *it;
            plugin->OnFrame(&fakeInterface);
        }
        // sleep 1 second
        sleep(1);
        fakeInterface.incrementFrame();
    }

    for (pluginlistiterator it = plugins.begin(); it != plugins.end(); it++)
    {
        plugin::IPlugin *plugin = *it;
        plugin->OnExit();
        delete plugin;
    }
    plugins.clear();

    // Close the library
    dlclose(handle);
    return 0;
}
