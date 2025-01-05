#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Utils/Utils.hpp"

namespace roo
{
    Texture::Texture(const std::string& path)
        : m_Path(path)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        std::string rp = GetExecutablePath()+ "/" + path;
        stbi_uc* data = stbi_load(rp.c_str(), &width, &height, &channels, 0);

        if (!data)
            ROO_LOG_ERROR("Could not load image");

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        switch (channels)
        {
        case 4:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;

        case 3:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;

        default:
            ROO_LOG_ERROR("Texture format not supported");
            break;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    uint32_t Texture::GetWidth()
    {
        return m_Width;
    }
    uint32_t Texture::GetHeight()
    {
        return m_Height;
    }

    void Texture::Bind(uint32_t slot)
    {
        glBindTextureUnit(slot, m_RendererID);
    }
}