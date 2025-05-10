#pragma once

#include <string>
#include <cstdint>

namespace raytracer {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");

        virtual ~Layer() = default;

        virtual void OnAttach()
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnUpdate(float timeStep, const std::uint32_t width, const std::uint32_t height)
        {
        }

        virtual void OnUIRender()
        {
        }

        const std::string& GetName() const;

    protected:
        std::string m_Name;
    };

}