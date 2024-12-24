#pragma once

#include "Core/Window.hpp"
#include "Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"

#include "Renderer/VertexBuffer.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/Shader.hpp"

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

        // TEMP
        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    };

    // Should be defined by client application
    Application* CreateApplication();
}