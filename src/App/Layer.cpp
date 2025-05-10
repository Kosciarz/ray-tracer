#include "Layer.hpp"

#include <string>

namespace raytracer {

    Layer::Layer(const std::string& name)
        : m_Name{name}
    {
    }

    const std::string& Layer::GetName() const
    {
        return m_Name;
    }

}