#include "Application.hpp"

#include "Log.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"

namespace roo
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    // TEMP
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case roo::ShaderDataType::Float:    return GL_FLOAT;
        case roo::ShaderDataType::Float2:   return GL_FLOAT;
        case roo::ShaderDataType::Float3:   return GL_FLOAT;
        case roo::ShaderDataType::Float4:   return GL_FLOAT;
        case roo::ShaderDataType::Int:      return GL_INT;
        case roo::ShaderDataType::Int2:     return GL_INT;
        case roo::ShaderDataType::Int3:     return GL_INT;
        case roo::ShaderDataType::Int4:     return GL_INT;
        case roo::ShaderDataType::Mat3:     return GL_FLOAT;
        case roo::ShaderDataType::Mat4:     return GL_FLOAT;
        case roo::ShaderDataType::Bool:     return GL_BOOL;
        }

        ROO_LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }

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
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 5] = {
            -0.5, -0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        };

        m_VertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "VertexPos" },
                { ShaderDataType::Float2, "color"}
            };

            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        GLuint indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));

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
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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