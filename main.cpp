#include <iostream>
#include <dlfcn.h>

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

    // Close the library
    dlclose(handle);
}
