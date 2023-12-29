#include "load_shared.h"
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>

namespace shared
{
    // Typedefs for the signature of the functions to load
    typedef void (*InitializeFunc)();
    typedef plugin::IPlugin *(*CreateFunc)();

    plugin::IPlugin *load_so_and_create_plugin(const char *soPath)
    {

        // Open the shared object
        void *handle = dlopen(soPath, RTLD_LAZY);
        if (!handle)
        {
            std::cerr << "Cannot open library: " << dlerror() << '\n';
            return nullptr;
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
                return nullptr;
            }
        }

        CreateFunc create = (CreateFunc)dlsym(handle, "create");
        {
            const char *dlsym_error = dlerror();
            if (dlsym_error)
            {
                std::cerr << "Cannot load symbol 'create': " << dlsym_error << '\n';
                dlclose(handle);
                return nullptr;
            }
        }

        // Use the function initialize();
        initialize();

        return create();

        // We intentionally leak the handle here, so that the shared object
        // stays loaded in memory.

        // Close the library
        // dlclose(handle);
    }
} // namespace shared
