#include "MouseEvent.hpp"

namespace roo
{
    MouseMovedEvent::MouseMovedEvent(const float x, const float y)
        : m_MouseX(x), m_MouseY(y)
    {
    }

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset)
    {
    }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    MouseButtonEvent::MouseButtonEvent(const MouseCode button)
        : m_Button(button)
    {
    }

    MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }
}