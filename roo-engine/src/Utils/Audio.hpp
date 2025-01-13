#pragma once

namespace roo
{
    class Audio
    {
    public:
        static void Init();
        static void Uninit();

    public:
        static void Play(const std::string& file);

    private:
        static Audio* s_Instance;

    };
}