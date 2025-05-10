#include "Interval.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    Interval::Interval()
        : m_Min{+g_Infinity}, m_Max{-g_Infinity}
    {
    }

    Interval::Interval(const double min, const double max)
        : m_Min{min}, m_Max{max}
    {
    }

    double Interval::Size() const
    {
        return m_Max - m_Min;
    }

    double Interval::Min() const
    {
        return m_Min;
    }

    double Interval::Max() const
    {
        return m_Max;
    }

    bool Interval::Contains(const double x) const
    {
        return m_Min <= x && x <= m_Max;
    }

    bool Interval::Surrounds(const double x) const
    {
        return m_Min < x && x < m_Max;
    }

}