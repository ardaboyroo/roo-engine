#include "Rectangle.hpp"

#include "Renderer/Renderer.hpp"

namespace roo
{
    Rectangle::Rectangle(glm::vec2 size, glm::vec2 position, glm::vec3 color)
        : m_Color({ color, 1.0f })
    {
        // Vertex shader
        std::string vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 a_VertexPosition;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_VertexPosition, 1.0);
}
)";

        // Fragment shader
        std::string fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
}
)";

        m_VertexArray.reset(new VertexArray());
        m_Shader.reset(new Shader(vertexSource, fragmentSource));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer(new VertexBuffer(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "Vertex Position" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[] = { 0, 1, 2 , 0, 2, 3 };
        std::shared_ptr<IndexBuffer> indexBuffer(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        SetSize(size);
        SetPosition(position);
    }

    Rectangle::~Rectangle()
    {
    }

    glm::vec3 Rectangle::GetColor()
    {
        return m_Color;
    }

    float Rectangle::GetAlpha()
    {
        return m_Color.a;
    }

    void Rectangle::SetColor(glm::vec3 color)
    {
        m_Color = glm::vec4(color, m_Color.a);
    }

    void Rectangle::SetAlpha(float alpha)
    {
        m_Color.a = alpha;
    }

    void Rectangle::Draw()
    {
        m_Shader->Bind();
        m_Shader->SetUniformMat4("u_Transform", m_Transform);
        m_Shader->SetUniformFloat4("u_Color", m_Color);
        Renderer::Draw(m_Shader, m_VertexArray);
    }
}