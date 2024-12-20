#include "roo.hpp"

class TestLayer : public roo::Layer
{
public:
    TestLayer()
        : Layer("TestLayer")
    {
        // Heaps and globals are not shared across DLL boundaries! 
        // You will need to call SetCurrentContext() + SetAllocatorFunctions()
        ImGui::SetCurrentContext(roo::Application::Get().GetImGuiContext());
    }

    void OnUpdate() override
    {

    }

    void OnEvent(roo::Event& event) override
    {
        if (event.GetEventType() == roo::EventType::KeyPressed)
        {
            roo::KeyPressedEvent& e = (roo::KeyPressedEvent&)event;
            std::string c;
            c += e.GetKeyCode();
            LOG_INFO(c);
        }
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("App Test");
        ImGui::Text("This is a test ImGui window from App");
        ImGui::End();
    }
};

class MyApp : public roo::Application
{
public:
    MyApp()
    {
        PushLayer(new TestLayer());
        SetBackgroundColor(1.0f, 1.0f, 0.0f);
    }
};

roo::Application* roo::CreateApplication()
{
    return new MyApp();
}