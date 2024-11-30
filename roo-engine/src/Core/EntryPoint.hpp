#pragma once

extern roo::Application* roo::CreateApplication();

int main(int argc, char** argv)
{
    roo::Core::Init();
    
    auto app = roo::CreateApplication();
    app->Run();
    delete app;
}