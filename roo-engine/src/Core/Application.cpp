#include "Application.hpp"
#include "Log.hpp"
#include "Events/ApplicationEvent.hpp"

roo::Application::Application()
{
}

roo::Application::~Application()
{
}

void roo::Application::Run()
{
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication))
    {
        ROO_LOG_INFO("Application event fired");
    }
    if (e.IsInCategory(EventCategoryInput))
    {
        ROO_LOG_ERROR("Input event fired");
    }

    while (true)
    {
    }
}