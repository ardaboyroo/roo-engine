#include "KeyEvent.hpp"

#include <sstream>

namespace roo
{
    //////////////////////////////////////
    // KeyEvent
    //////////////////////////////////////

    KeyEvent::KeyEvent(const KeyCode keycode)
        : m_KeyCode(keycode)
    {
    }

    KeyCode KeyEvent::GetKeyCode() const
    {
        return m_KeyCode;
    }


    //////////////////////////////////////
    // KeyPressedEvent
    //////////////////////////////////////

    KeyPressedEvent::KeyPressedEvent(const KeyCode keycode, bool isRepeat)
        : KeyEvent(keycode), m_IsRepeat(isRepeat)
    {
    }

    bool KeyPressedEvent::IsRepeat() const
    {
        return m_IsRepeat;
    }

    std::string KeyPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
        return ss.str();
    }


    //////////////////////////////////////
    // KeyReleasedEvent
    //////////////////////////////////////

    KeyReleasedEvent::KeyReleasedEvent(const KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string KeyReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }


    //////////////////////////////////////
    // KeyTypedEvent
    //////////////////////////////////////


    KeyTypedEvent::KeyTypedEvent(const KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string KeyTypedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_KeyCode;
        return ss.str();
    }
}