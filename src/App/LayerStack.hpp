#pragma once

#include <vector>
#include <iostream>

#include "Layer.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        LayerStack(const LayerStack&) = delete;
        LayerStack& operator=(const LayerStack&) = delete;

        LayerStack(LayerStack&&) noexcept = default;
        LayerStack& operator=(LayerStack&&) noexcept = default;

        void PushLayer(Scope<Layer> layer);

        void PushOverlay(Scope<Layer> layer);

        void PopLayer(Layer* layer);

        void PopOverlay(Layer* layer);

        std::vector<Scope<Layer>>::iterator begin();
        std::vector<Scope<Layer>>::iterator end();

        std::vector<Scope<Layer>>::const_iterator begin() const;
        std::vector<Scope<Layer>>::const_iterator end() const;

    private:
        std::vector<Scope<Layer>> m_Layers;
        std::size_t m_LayerInsertIndex;
    };


    inline std::vector<Scope<Layer>>::iterator LayerStack::begin()
    {
        return m_Layers.begin();
    }

    inline std::vector<Scope<Layer>>::iterator LayerStack::end()
    {
        return m_Layers.end();
    }

    inline std::vector<Scope<Layer>>::const_iterator LayerStack::begin() const
    {
        return m_Layers.begin();
    }

    inline std::vector<Scope<Layer>>::const_iterator LayerStack::end() const
    {
        return m_Layers.end();
    }
}