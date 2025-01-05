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
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        if (!s_Instance)
            s_Instance = this;
        else
            ROO_LOG_ERROR("Application already exists!");

        m_Window = std::make_unique<Window>(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            double time = glfwGetTime();
            m_DeltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            Renderer::Clear();


            // Update all layers
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(m_DeltaTime);

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

    Camera& Application::GetCamera()
    {
        return m_Camera;
    }

    bool Application::GetVSync()
    {
        return m_Window->IsVSync();
    }

    void Application::SetBackgroundColor(float red, float green, float blue)
    {
        m_Window->SetBackgroundColor(red, green, blue);
    }

    void Application::SetVSync(bool enabled)
    {
        m_Window->SetVSync(enabled);
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