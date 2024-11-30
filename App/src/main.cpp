#include "roo.hpp"

class MyApp : public roo::Application
{
public:
    MyApp()
    {
        
    }
};

roo::Application* roo::CreateApplication()
{
    return new MyApp();
}