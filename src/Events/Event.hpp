#pragma once

#include <string>
#include <functional>

namespace raytracer {

    enum class EventType
    {
        WindowClose = 0, WindowResize,
        KeyPressed, KeyReleased
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;

        virtual const char* GetName() const = 0;

        virtual const std::string& ToString() const = 0;

    public:
        bool Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event{event}
        {
        }

        template <typename T, typename Func>
        bool Dispatch(Func&& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

}