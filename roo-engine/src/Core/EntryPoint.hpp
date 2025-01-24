#pragma once

extern roo::Application* roo::CreateApplication();

// This is the entry point to the application.
// Define the roo::Application* roo::CreateApplication() function 
// from App side to pass an instance of your application.
int main(int argc, char** argv)
{
    roo::Core::Init();
    
    auto app = roo::CreateApplication();

    // Initialize ImGui on the App side since heaps and globals 
    // aren't shared across DLL boundaries
    ImGui::SetCurrentContext(roo::Application::Get().GetImGuiContext());

    app->Run();
    delete app;

    roo::Core::Uninit();
}