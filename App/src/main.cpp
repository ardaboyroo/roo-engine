#include "roo.hpp"

class TestLayer : public roo::Layer
{
public:
    TestLayer()
        : Layer("TestLayer")
    {

    }

    void OnUpdate() override
    {
        LOG_INFO("OnUpdate from App called!");
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