#pragma once

#include "Declarations.hpp"
#include <memory>

namespace roo
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

    protected:
        void SetBackgroundColor(float red, float green, float blue);

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // Should be defined by client application
    Application* CreateApplication();
}