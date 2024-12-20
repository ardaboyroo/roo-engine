#pragma once

#include "Core/LayerStack.hpp"
#include "Core/Window.hpp"
#include "Events/ApplicationEvent.hpp"
#include "ImGui/ImGuiLayer.hpp"

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

        Window& GetWindow();

        ImGuiContext* GetImGuiContext() { return m_ImGuiLayer->GetImGuiContext(); }

        static Application& Get();

    protected:
        void SetBackgroundColor(float red, float green, float blue);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;

        LayerStack m_LayerStack;
        bool m_Running = true;
        ImGuiLayer* m_ImGuiLayer;
        static Application* s_Instance;
    };

    // Should be defined by client application
    Application* CreateApplication();
}