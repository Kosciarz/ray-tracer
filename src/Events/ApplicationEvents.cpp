#include "ApplicationEvents.hpp"

#include <cstdint>
#include <string>

namespace raytracer {

    EventType WindowCloseEvent::GetEventType() const
    {
        return EventType::WindowClose;
    }

    const char* WindowCloseEvent::GetName() const
    {
        return "WindowCloseEvent";
    }

    
    WindowResizeEvent::WindowResizeEvent(const std::uint32_t width, const std::uint32_t height)
        : m_Width{width}, m_Height{height}
    {
    }

    std::uint32_t WindowResizeEvent::GetWidth() const
    {
        return m_Width;
    }

    std::uint32_t WindowResizeEvent::GetHeight() const
    {
        return m_Height;
    }

    EventType WindowResizeEvent::GetEventType() const
    {
        return EventType::WindowResize;
    }

    const char* WindowResizeEvent::GetName() const
    {
        return "WindowResizeEvent";
    }

    std::string WindowResizeEvent::ToString() const
    {
        return "WindowResizeEvent: " + std::to_string(m_Width) + " " + std::to_string(m_Height);
    }

}