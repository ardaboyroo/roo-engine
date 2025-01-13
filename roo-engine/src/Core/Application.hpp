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
    // This is the "entry point" for your application. Inherit from roo::Application and
    // define the "roo::Application* CreateApplication()" in one of your files and return an 
    // instance of your subclass. An example can be found in roo.hpp
    class Application
    {
    public:
        Application(WindowSettings& settings = WindowSettings());
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