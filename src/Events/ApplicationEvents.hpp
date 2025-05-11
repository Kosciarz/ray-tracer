#pragma once

#include <cstdint>

#include "Event.hpp"

namespace raytracer {

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EventType GetEventType() const override;

        const char* GetName() const override;

        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(const std::uint32_t width, const std::uint32_t height);

        std::uint32_t GetWidth() const;

        std::uint32_t GetHeight() const;

        EventType GetEventType() const override;

        const char* GetName() const override;

        std::string ToString() const override;

        EVENT_CLASS_TYPE(WindowResize)

    private:
        std::uint32_t m_Width, m_Height;
    };

}