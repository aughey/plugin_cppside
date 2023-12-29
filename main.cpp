#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "plugin.h"
#include "local_plugin.h"
#include <unistd.h>

typedef void (*InitializeFunc)();
typedef plugin::IPlugin *(*CreateFunc)();

class FakeInterface : public plugin::IInterface
{
public:
    FakeInterface() : frame(0) {}
    virtual ~FakeInterface() = default;
    void incrementFrame()
    {
        frame++;
    }
    virtual std::string getName() override
    {
        return "FakeInterface";
    }
    virtual ssize_t getFrame() override
    {
        return frame;
    }
    virtual double getPositionX() override
    {
        return 3.14;
    }
    virtual double getPositionY() override
    {
        return 0.159;
    }
    virtual double getPositionZ() override
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
    std::vector<plugin::IPlugin *> plugins;
    plugins.push_back(new LocalPlugin());
    plugins.push_back(create());
    FakeInterface fakeInterface;

    while (true)
    {
        for (auto plugin : plugins)
        {
            plugin->OnFrame(&fakeInterface);
        }
        // sleep 1 second
        sleep(1);
        fakeInterface.incrementFrame();
    }

    // Close the library
    dlclose(handle);
}
