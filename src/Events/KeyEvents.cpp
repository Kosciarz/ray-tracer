#include "KeyEvents.hpp"

#include <string>
#include <format>
#include <stdexcept>

#include "Event.hpp"

static const char* KeyToString(const raytracer::Key& key)
{
    using raytracer::Key;
    switch (key)
    {
        case Key::ESCAPE: return "ESCAPE";
        case Key::R: return "R";
        case Key::W: return "W";
        case Key::A: return "A";
        case Key::S: return "S";
        case Key::D: return "D";
        default:
            throw std::runtime_error{"Invalid Key Type."};
    }
}

namespace raytracer {

    KeyPressedEvent::KeyPressedEvent(const Key& key)
        : m_Key{key}
    {
    }

    Key KeyPressedEvent::GetKey() const
    {
        return m_Key;
    }

    EventType KeyPressedEvent::GetEventType() const
    {
        return EventType::KeyPressed;
    }

    const char* KeyPressedEvent::GetName() const
    {
        return "KeyPressedEvent";
    }

    std::string KeyPressedEvent::ToString() const
    {
        return std::format("{}: {}", GetName(), KeyToString(m_Key));
    }

}
