#pragma once

namespace roo
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        uint32_t GetWidth();
        uint32_t GetHeight();

        void Bind(uint32_t slot = 0);

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
    };
}