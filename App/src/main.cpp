#include "roo.hpp"

#include <memory>

class TestLayer : public roo::Layer
{
public:
    TestLayer()
        : Layer("TestLayer"), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
    {
        // Heaps and globals are not shared across DLL boundaries! 
        // You will need to call SetCurrentContext() + SetAllocatorFunctions()
        ImGui::SetCurrentContext(roo::Application::Get().GetImGuiContext());
    }

    void OnAttach()
    {
        m_VertexArray = std::make_shared<roo::VertexArray>();

        float vertices[3 * 5] = {
            -0.5, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        };

        std::shared_ptr<roo::VertexBuffer> vertexBuffer(new roo::VertexBuffer(vertices, sizeof(vertices)));


        roo::BufferLayout layout = {
            { roo::ShaderDataType::Float3, "VertexPos" },
            { roo::ShaderDataType::Float2, "color"}
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);


        unsigned int indices[3] = { 0, 1, 2 };
        std::shared_ptr<roo::IndexBuffer> indexBuffer(new roo::IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 clr;

uniform mat4 u_ViewProjection;

out vec2 vClr;

void main()
{
    vClr = clr;
    gl_Position = u_ViewProjection * vec4(VertexPos, 1.0f);
}
        )";

        std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vClr;

void main()
{
    color = vec4(vClr, 0.5f, 1.0f);
}
        )";

        m_Shader.reset(new roo::Shader(vertexSrc, fragmentSrc));

        ///////////////////////////////
        //BACKGROUND                ///
        ///////////////////////////////

        m_BackgroundVertexArray = std::make_shared<roo::VertexArray>();

        float backgroundVertices[] = {
            -0.75,  -0.75f, 0.0f, 0.0f, 0.0f,
             0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
             0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
            -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<roo::VertexBuffer> backgroundVertexBuffer(
            new roo::VertexBuffer(backgroundVertices, sizeof(backgroundVertices)));


        roo::BufferLayout backgroundLayout = {
            { roo::ShaderDataType::Float3, "VertexPos" },
            { roo::ShaderDataType::Float2, "TextureCoordinate"}
        };

        backgroundVertexBuffer->SetLayout(backgroundLayout);
        m_BackgroundVertexArray->AddVertexBuffer(backgroundVertexBuffer);


        unsigned int backgroundIndices[] = { 0, 1, 2 , 0, 2, 3 };
        std::shared_ptr<roo::IndexBuffer> backgroundIndexBuffer(new roo::IndexBuffer(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));
        m_BackgroundVertexArray->SetIndexBuffer(backgroundIndexBuffer);

        std::string backgroundVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 TexCoord;

uniform mat4 u_ViewProjection;

out vec2 texCoord;

void main()
{
    texCoord = TexCoord;
    gl_Position = u_ViewProjection * vec4(VertexPos, 1.0f);
}
        )";

        std::string backgroundFragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, texCoord);
}
        )";

        m_BackgroundShader.reset(new roo::Shader(backgroundVertexSrc, backgroundFragmentSrc));

        // Make sure to copy the assets folder from App to build/bin/App/(Debug or Release)/
        m_Texture.reset(new roo::Texture("assets/Checkerboard.png"));
        m_TransparentTexture.reset(new roo::Texture("assets/OpenGLlogo.png"));
        m_BackgroundShader->Bind();
        m_BackgroundShader->SetUniformInt("u_Texture", 0);
    }

    void OnUpdate(float deltaTime) override
    {
        if (roo::Input::IsKeyPressed(roo::Key::Left))
            m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
        else if (roo::Input::IsKeyPressed(roo::Key::Right))
            m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
        if (roo::Input::IsKeyPressed(roo::Key::Up))
            m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
        else if (roo::Input::IsKeyPressed(roo::Key::Down))
            m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;

        roo::Camera& cam = roo::Application::Get().GetCamera();

        cam.SetPosition(m_CameraPosition);

        roo::Renderer::BeginScene();

        m_Texture->Bind();
        roo::Renderer::Draw(m_BackgroundShader, m_BackgroundVertexArray);
        m_TransparentTexture->Bind();
        roo::Renderer::Draw(m_BackgroundShader, m_BackgroundVertexArray);
        roo::Renderer::Draw(m_Shader, m_VertexArray);

        roo::Renderer::EndScene();
    }

    void OnEvent(roo::Event& event) override
    {
        if (event.GetEventType() == roo::EventType::KeyPressed)
        {
            roo::KeyPressedEvent& e = (roo::KeyPressedEvent&)event;
            std::string c;
            c += e.GetKeyCode();
            //LOG_INFO(c);
        }
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Debug");
        std::string s = "Framerate: ";
        s += S(ImGui::GetIO().Framerate);
        ImGui::Text(s.c_str());
        ImGui::End();
    }

private:
    bool isVSync = true;

    std::shared_ptr<roo::Shader> m_Shader;
    std::shared_ptr<roo::VertexArray> m_VertexArray;

    std::shared_ptr<roo::Shader> m_BackgroundShader;
    std::shared_ptr<roo::VertexArray> m_BackgroundVertexArray;

    std::shared_ptr<roo::Texture> m_Texture, m_TransparentTexture;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
};

class MyApp : public roo::Application
{
public:
    MyApp()
    {
        PushLayer(new TestLayer());
        SetBackgroundColor(0.2f, 0.25f, 0.3f);
    }
};

roo::Application* roo::CreateApplication()
{
    return new MyApp();
}