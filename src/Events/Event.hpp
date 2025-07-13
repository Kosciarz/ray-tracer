#pragma once

#include <string>

namespace raytracer {

    enum class EventType
    {
        WindowClose = 0, WindowResize,
        KeyPressed
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;

        virtual const char* GetName() const = 0;

        virtual std::string ToString() const
        {
            return GetName();
        }

    public:
        bool Handled = false;
    };

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& e)
            : m_Event{e}
        {
        }

        template <typename T, typename Func>
        bool Dispatch(const Func& func)
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
