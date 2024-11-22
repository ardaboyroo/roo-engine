#pragma once

extern roo::Application* roo::CreateApplication();

int main(int argc, char** argv)
{
    auto app = roo::CreateApplication();
    app->Run();
    delete app;
}