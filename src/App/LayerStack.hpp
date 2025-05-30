#pragma once

#include <vector>
#include <memory>

#include "Layer.hpp"

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

        void PushLayer(std::unique_ptr<Layer> layer);

        void PushOverlay(std::unique_ptr<Layer> layer);

        void PopLayer(Layer* layer);

        void PopOverlay(Layer* layer);

        std::vector<std::unique_ptr<Layer>>::iterator begin();
        std::vector<std::unique_ptr<Layer>>::iterator end();
        std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin();
        std::vector<std::unique_ptr<Layer>>::reverse_iterator rend();

        std::vector<std::unique_ptr<Layer>>::const_iterator begin() const;
        std::vector<std::unique_ptr<Layer>>::const_iterator end() const;
        std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rbegin() const;
        std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rend() const;

    private:
        std::vector<std::unique_ptr<Layer>> m_Layers;
        std::size_t m_LayerInsertIndex;
    };


    inline std::vector<std::unique_ptr<Layer>>::iterator LayerStack::begin()
    {
        return m_Layers.begin();
    }

    inline std::vector<std::unique_ptr<Layer>>::iterator LayerStack::end()
    {
        return m_Layers.end();
    }

    inline std::vector<std::unique_ptr<Layer>>::reverse_iterator LayerStack::rbegin()
    {
        return m_Layers.rbegin();
    }

    inline std::vector<std::unique_ptr<Layer>>::reverse_iterator LayerStack::rend()
    {
        return m_Layers.rend();
    }

    inline std::vector<std::unique_ptr<Layer>>::const_iterator LayerStack::begin() const
    {
        return m_Layers.begin();
    }

    inline std::vector<std::unique_ptr<Layer>>::const_iterator LayerStack::end() const
    {
        return m_Layers.end();
    }

    inline std::vector<std::unique_ptr<Layer>>::const_reverse_iterator LayerStack::rbegin() const
    {
        return m_Layers.rbegin();
    }

    inline std::vector<std::unique_ptr<Layer>>::const_reverse_iterator LayerStack::rend() const
    {
        return m_Layers.rend();
    }

}