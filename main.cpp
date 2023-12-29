#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "plugin.h"
#include "local_plugin.h"
#include <unistd.h>

typedef void (*InitializeFunc)();

int main() {
    // Path to the shared object
    const char* soPath = "/path/to/your/library.so";

    // Open the shared object
    void* handle = dlopen(soPath, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // Reset errors
    dlerror();

    // Load the symbol
    InitializeFunc initialize = (InitializeFunc) dlsym(handle, "initialize");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'initialize': " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    // Use the function
    initialize();

    // Local our local plugin
    std::vector<plugin::IPlugin*> plugins;
    plugins.push_back(new LocalPlugin());

    while(true) {
        for (auto plugin : plugins) {
            plugin->OnFrame(nullptr);
        }
        // sleep 1 second
        sleep(1);
    }

    // Close the library
    dlclose(handle);
}
