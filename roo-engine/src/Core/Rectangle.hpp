#pragma once

#include "GameObject.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"

#include <string>
#include <memory>

namespace roo
{
    // This is an engine provided rectangle class to render quads.
    class Rectangle : public GameObject
    {
    public:
        Rectangle(glm::vec2 size, glm::vec2 position, glm::vec3 color = {1.0f, 1.0f, 1.0f});
        ~Rectangle();

        glm::vec3 GetColor();
        float GetAlpha();

        void SetColor(glm::vec3 color);
        void SetAlpha(float alpha);

        virtual void Draw() override;

    private:
        glm::vec4 m_Color;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;
    };
}