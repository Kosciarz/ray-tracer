#pragma once

#include "Event.hpp"

#include <string>

namespace raytracer {

    enum class Key
    {
        ESCAPE,
        R,
        W,
        A,
        S,
        D
    };

    class KeyPressedEvent final : public Event
    {
    public:
        KeyPressedEvent(const Key& key);
    
        [[nodiscard]] Key GetKey() const;

        [[nodiscard]] EventType GetEventType() const override; 
        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(KeyPressed);

    private:
        Key m_Key;
    };

}
