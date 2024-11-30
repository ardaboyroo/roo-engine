#pragma once

#include "Event.hpp"
#include "Core/KeyCodes.hpp"

namespace roo
{
    // Base class for different key events
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const;

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(const KeyCode keycode);

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode keycode, bool isRepeat = false);

        bool IsRepeat() const;

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode keycode);

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode keycode);

        std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyTyped)
    };
}