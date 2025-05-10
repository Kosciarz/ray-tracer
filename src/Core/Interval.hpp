#pragma once

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class Interval
    {
    public:
        Interval();

        Interval(const double min, const double max);

        double Size() const;

        double Min() const;

        double Max() const;

        bool Contains(const double x) const;

        bool Surrounds(const double x) const;

    public:
        static const Interval s_Empty;
        static const Interval s_Universe;

    private:
        double m_Min, m_Max;
    };


    inline const Interval Interval::s_Empty = Interval{+g_Infinity, -g_Infinity};
    inline const Interval Interval::s_Universe = Interval{-g_Infinity, +g_Infinity};

}