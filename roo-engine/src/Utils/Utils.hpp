#pragma once

#include "Core/Core.hpp"

#include <string>

namespace roo
{
    // Returns the directory path of the executable at runtime
    std::string GetExecutablePath();

    struct DirectoryItem
    {
        std::string FullPath;
        std::string RelativePath;
        std::string FileName;
        std::string FileExtension;

        DirectoryItem(const std::string& path);
    };

    std::vector<roo::DirectoryItem> GetDirectoryItems(std::string directoryPath, bool searchRecursive = false);
}