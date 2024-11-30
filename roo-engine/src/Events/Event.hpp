#pragma once

#include "Core/Core.hpp"

#include <string>
#include <functional>

namespace roo
{
    // Events in roo-engine are currently blocking, meaning that when an event
    // occurs it immediately gets dispatched.
    // A better way to do this is to create an event queue where all events get
    // dispatched during the "event handling" phase.
    // TODO: implement event queue.

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // Event category flags.
    enum EventCategory
    {
        None = 0,																																			// 00000
        EventCategoryApplication = BITL(0),						// 00001
        EventCategoryInput = BITL(1),						// 00010
        EventCategoryKeyboard = BITL(2),						// 00100
        EventCategoryMouse = BITL(3),						// 01000
        EventCategoryMouseButton = BITL(4)							// 10000
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
        virtual EventType GetEventType() const override { return GetStaticType(); }\
        virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    // Base class for all Events
    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category);
    };

    //
    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event);

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& func);

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e);
}