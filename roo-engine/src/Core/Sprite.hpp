#pragma once

#include "GameObject.hpp"
#include "Texture.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"

#include <string>
#include <memory>

namespace roo
{
    // This is an engine provided sprite class to render texture files.
    // NOTE: the texture must be in the same directory as the executable.
    class Sprite : public GameObject
    {
    public:
        Sprite(std::string filepath);
        ~Sprite();

        virtual void Draw() override;

    private:
        std::shared_ptr<Texture> m_Texture;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}