#include "Core.hpp"

#include "Log.hpp"
#include "Utils/Audio.hpp"
#include "Renderer/Renderer.hpp"

namespace roo
{
    void Core::Init()
    {
        Log::Init();
        Audio::Init();
    }

    void Core::Uninit()
    {
        Audio::Uninit();
    }
}