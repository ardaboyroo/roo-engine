#pragma once

#include "Core/Layer.hpp"

struct ImGuiContext;
namespace roo
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;
        void OnEvent(Event& event) override;

        void Begin();
        void End();

        ImGuiContext* GetImGuiContext() { return m_ImGuiContext; }

        ImGuiContext* m_ImGuiContext;
    private:
    };
}