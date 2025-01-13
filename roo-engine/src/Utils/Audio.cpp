#include "Audio.hpp"

#include "Utils.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include <string>

namespace roo
{
    static ma_engine engine;

    Audio* Audio::s_Instance = nullptr;

    void Audio::Init()
    {
        if (!s_Instance)
            s_Instance = new Audio;
        else
            ROO_LOG_ERROR("Audio engine already initialized!");

        if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
        {
            ROO_LOG_ERROR("Failed to initialize audio engine!");
        }
    }

    void Audio::Uninit()
    {
        ma_engine_uninit(&engine);
    }

    void Audio::Play(const std::string& file)
    {
        std::string rp = GetExecutablePath() + '/' + file;
        ma_result result = ma_engine_play_sound(&engine, rp.c_str(), NULL);
        if (result != MA_SUCCESS)
        {
            ROO_LOG_ERROR("Failed to play audio \"" + rp + '"');
        }
    }
}