#pragma once

#include "plugin.h"

namespace shared {
    /// @brief  Load a shared object and create a plugin
    /// @param soPath - Path to the shared object
    /// @return - instantiated plugin
    plugin::IPlugin *load_so_and_create_plugin(const char *soPath);
}