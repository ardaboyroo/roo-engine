#include "Event.hpp"

namespace roo
{
    bool Event::IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }

    EventDispatcher::EventDispatcher(Event& event)
        : m_Event(event)
    {
    }

    template<typename T, typename F>
    inline bool EventDispatcher::Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled |= func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}