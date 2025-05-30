#include "LayerStack.hpp"

#include <vector>
#include <memory>
#include <algorithm>

namespace raytracer {

    LayerStack::LayerStack()
        : m_LayerInsertIndex{0}
    {
    }

    LayerStack::~LayerStack()
    {
        for (const auto& layer : m_Layers)
        {
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
    {
        layer->OnAttach();
        m_Layers.insert(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(std::unique_ptr<Layer> layer)
    {
        layer->OnAttach();
        m_Layers.push_back(std::move(layer));
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        const auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
            [&layer](const std::unique_ptr<Layer>& ptr)
            {
                return ptr.get() == layer;
            });

        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer)
    {
        const auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
            [&layer](const std::unique_ptr<Layer>& ptr)
            {
                return ptr.get() == layer;
            });

        if (it != m_Layers.end())
        {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }

}