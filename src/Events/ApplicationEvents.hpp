#pragma once

#include <cstdint>

#include "Event.hpp"

namespace raytracer {

    class WindowCloseEvent final : public Event
    {
    public:
        WindowCloseEvent() = default;

        EventType GetEventType() const override;

        const char* GetName() const override;

        EVENT_CLASS_TYPE(WindowClose)
    };

    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(const std::uint32_t width, const std::uint32_t height);

        [[nodiscard]] std::uint32_t GetWidth() const;
        [[nodiscard]] std::uint32_t GetHeight() const;

        [[nodiscard]] EventType GetEventType() const override;
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(WindowResize)

    private:
        std::uint32_t m_Width, m_Height;
    };

}
