#include "Sprite.hpp"

#include "Renderer/Renderer.hpp"

namespace roo
{

    Sprite::Sprite(std::string filepath)
    {
        // Vertex shader
        std::string vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 a_VertexPosition;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_VertexPosition, 1.0);
}
)";

        // Fragment shader
        std::string fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord);
}
)";
        m_VertexArray.reset(new VertexArray());
        m_Shader.reset(new Shader(vertexSource, fragmentSource));
        m_Texture.reset(new Texture(filepath));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer(new VertexBuffer(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "Vertex Position" },
            { ShaderDataType::Float2, "Texture Coordinate"}
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[] = { 0, 1, 2 , 0, 2, 3 };
        std::shared_ptr<IndexBuffer> indexBuffer(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        SetSize({m_Texture->GetWidth(), m_Texture->GetHeight()});
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Draw()
    {
        m_Texture->Bind();
        m_Shader->Bind();
        m_Shader->SetUniformInt("u_Texture", 0);
        m_Shader->SetUniformMat4("u_Transform", m_Transform);
        Renderer::Draw(m_Shader, m_VertexArray);
    }
}