#pragma once

#include <string>

#include "Events/Event.hpp"

namespace raytracer {

    class Layer
    {
    public:
        explicit Layer(const std::string& name = "Layer");

        virtual ~Layer() = default;

        virtual void OnAttach()
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnUpdate(float timeStep)
        {
        }

        virtual void OnUIRender()
        {
        }

        virtual void OnEvent(Event& e)
        {
        }

        const std::string& GetName() const;

    protected:
        std::string m_Name;
    };

}