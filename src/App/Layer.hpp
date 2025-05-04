#pragma once

#include <cstdint>

namespace raytracer {

    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach()
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnUpdate(float timeStep, std::uint32_t width, std::uint32_t height)
        {
        }

        virtual void OnUIRender()
        {
        }

    };

}