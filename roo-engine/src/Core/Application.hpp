#pragma once

#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"

#include "Renderer/VertexBuffer.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Camera.hpp"

#include <memory>

namespace roo
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        static Application& Get();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    public:
        Window& GetWindow();

        ImGuiContext* GetImGuiContext() { return m_ImGuiLayer->GetImGuiContext(); }

        Camera& GetCamera();

        bool GetVSync();

    public:
        void SetBackgroundColor(float red, float green, float blue);

        void SetVSync(bool enabled);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;

        LayerStack m_LayerStack;
        bool m_Running = true;
        ImGuiLayer* m_ImGuiLayer;
        static Application* s_Instance;

        Camera m_Camera;

        double m_LastFrameTime;
        float m_DeltaTime;
    };

    // Should be defined by client application
    Application* CreateApplication();
}