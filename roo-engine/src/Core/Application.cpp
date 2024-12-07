#include "Application.hpp"
#include "Log.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Window.hpp"

namespace roo
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::make_unique<Window>(BIND_EVENT_FN(Application::OnEvent));
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    void Application::SetBackgroundColor(float red, float green, float blue)
    {
        m_Window->SetBackgroundColor(red, green, blue);
    }

    void Application::OnEvent(Event& e)
    {
        ROO_LOG_INFO("Application::OnEvent called!");
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}