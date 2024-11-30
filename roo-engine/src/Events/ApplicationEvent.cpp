#include "ApplicationEvent.hpp"

namespace roo
{
    WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height)
    {
    }

    std::string WindowResizeEvent::ToString() const
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }
}