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

    std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}