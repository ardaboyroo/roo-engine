#include "roo.hpp"

class MyApp : public roo::Application
{
public:
    MyApp()
    {
        SetBackgroundColor(1.0f, 1.0f, 0.0f);
    }
};

roo::Application* roo::CreateApplication()
{
    return new MyApp();
}