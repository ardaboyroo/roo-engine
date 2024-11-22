#pragma once

namespace roo
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // Should be defined by client application
    Application* CreateApplication();
}