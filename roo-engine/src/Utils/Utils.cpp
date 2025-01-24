#include "Utils.hpp"

#include <windows.h>
#include <filesystem>

namespace roo
{
    std::string GetExecutablePath()
    {
        char buffer[256];
        GetModuleFileNameA(NULL, buffer, 256);
        std::string exePath = std::string(buffer);
        size_t pos = exePath.find_last_of("\\/");
        return exePath.substr(0, pos) + '\\';
    }

    DirectoryItem::DirectoryItem(const std::string& path)
    {
        FullPath = path;

        RelativePath = path.substr(GetExecutablePath().length());

        size_t dot = path.find_last_of(".");
        FileExtension = path.substr(dot + 1);
        
        auto start = path.find_last_of("\\/") + 1;
        FileName = path.substr(start, dot - start);
    }

    std::vector<roo::DirectoryItem> roo::GetDirectoryItems(std::string directoryPath, bool searchRecursive)
    {
        namespace fs = std::filesystem;

        std::vector<DirectoryItem> items;

        try
        {
            // Estimate initial capacity to minimize reallocations
            size_t estimatedSize = std::distance(fs::directory_iterator(directoryPath), fs::directory_iterator());
            items.reserve(estimatedSize);


            if (searchRecursive)
            {
                for (const auto& entry : fs::recursive_directory_iterator(directoryPath))
                {
                    if (fs::is_regular_file(entry.status()))
                    {
                        items.emplace_back(entry.path().string());
                    }
                }
            }
            else
            {
                for (const auto& entry : fs::directory_iterator(directoryPath))
                {
                    if (fs::is_regular_file(entry.status()))
                    {
                        items.emplace_back(entry.path().string());
                    }
                }
            }
        }
        catch (const fs::filesystem_error& e)
        {
            std::string error = "Filesystem error: ";
            error += e.what();
            ROO_LOG_ERROR(error);
        }
        catch (const std::exception& e)
        {
            ROO_LOG_ERROR(e.what());
        }

        return items;
    }
}