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
    FakeInterface() : frame(0) {}
    virtual ~FakeInterface() {}
    void incrementFrame()
    {
        frame++;
    }
    virtual std::string getName()
    {
        return "FakeInterface";
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
};

int main()
{
    // Path to the shared object
    const char *soPath = "build/dynamic_plugin/libdynamic_plugin.so";

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
    plugins.push_back(new LocalPlugin());
    plugins.push_back(create());
    FakeInterface fakeInterface;

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

    // Close the library
    dlclose(handle);
}
