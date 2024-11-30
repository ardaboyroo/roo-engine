#include "Core.hpp"
#include "Log.hpp"

namespace roo
{
    void Core::Init()
    {
        Log::Init();

        ROO_LOG_INFO("Initializing roo-engine...");

        ROO_LOG_INFO("roo-engine is initialized!");
    }
}