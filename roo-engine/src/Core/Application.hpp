#pragma once

#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Core/Window.hpp"

#include <memory>

namespace roo
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    protected:
        void SetBackgroundColor(float red, float green, float blue);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;
    };

    // Should be defined by client application
    Application* CreateApplication();
}