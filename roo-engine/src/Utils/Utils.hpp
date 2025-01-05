#pragma once

#include <windows.h>

#include <string>

namespace roo
{
    // Returns the executable path at runtime
    std::string GetExecutablePath()
    {
        char buffer[256];
        GetModuleFileNameA(NULL, buffer, 256);
        std::string exePath = std::string(buffer);
        size_t pos = exePath.find_last_of("\\/");
        return exePath.substr(0, pos);
    }
}