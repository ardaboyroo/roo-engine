#include "ImGuiLayer.hpp"

#include "Core/Application.hpp"

namespace roo
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer"), m_ImGuiContext(nullptr)
    {
    }
    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        m_ImGuiContext = ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().m_GLFWWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnImGuiRender()
    {
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);

        //ImGui::Begin("Test");
        //ImGui::Bullet();
        //ImGui::Text("This is my test window");
        //ImGui::End();
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
    }
}