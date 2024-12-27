#include "Application.hpp"

#include "Log.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"

#include "Renderer/Renderer.hpp"

namespace roo
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        if (!s_Instance)
            s_Instance = this;
        else
            ROO_LOG_ERROR("Application already exists!");

        m_Window = std::make_unique<Window>(BIND_EVENT_FN(Application::OnEvent));
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // TEMP
        m_VertexArray = std::make_shared<VertexArray>();

        float vertices[3 * 5] = {
            -0.5, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        };

        std::shared_ptr<VertexBuffer> vertexBuffer(new VertexBuffer(vertices, sizeof(vertices)));


        BufferLayout layout = {
            { ShaderDataType::Float3, "VertexPos" },
            { ShaderDataType::Float2, "color"}
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);


        GLuint indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer(new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 VertexPos;
layout(location = 1) in vec2 clr;

out vec2 vClr;

void main()
{
    vClr = clr;
    gl_Position = vec4(VertexPos, 1.0f);
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

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        ///////////////////////////////
        //BACKGROUND                ///
        ///////////////////////////////

        m_BackgroundVertexArray = std::make_shared<VertexArray>();

        float backgroundVertices[] = {
            -0.75, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f,
        };

        std::shared_ptr<VertexBuffer> backgroundVertexBuffer(new VertexBuffer(backgroundVertices, sizeof(backgroundVertices)));


        BufferLayout backgroundLayout = {
            { ShaderDataType::Float3, "VertexPos" }
        };

        backgroundVertexBuffer->SetLayout(backgroundLayout);
        m_BackgroundVertexArray->AddVertexBuffer(backgroundVertexBuffer);


        GLuint backgroundIndices[] = { 0, 1, 2 , 0, 2, 3 };
        std::shared_ptr<IndexBuffer> backgroundIndexBuffer(new IndexBuffer(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));
        m_BackgroundVertexArray->SetIndexBuffer(backgroundIndexBuffer);

        std::string backgroundVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 VertexPos;

out vec3 vPos;

void main()
{
    vPos = VertexPos;
    gl_Position = vec4(VertexPos, 1.0f);
}
        )";

        std::string backgroundFragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vPos;

void main()
{
    color = vec4(vPos, 1.0f);
}
        )";

        m_BackgroundShader.reset(new Shader(backgroundVertexSrc, backgroundFragmentSrc));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            Renderer::Clear();

            m_BackgroundShader->Bind();
            Renderer::Draw(m_BackgroundVertexArray);

            m_Shader->Bind();
            Renderer::Draw(m_VertexArray);

            // Update all layers
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            // Draw imgui buffers from all layers
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            // Draw to the screen
            m_Window->OnUpdate();
        }
    }

    void Application::SetBackgroundColor(float red, float green, float blue)
    {
        m_Window->SetBackgroundColor(red, green, blue);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    Window& Application::GetWindow()
    {
        return *m_Window;
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}