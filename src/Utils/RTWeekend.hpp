#pragma once

#include <limits>
#include <numbers>

namespace raytracer {
    
    inline constexpr double g_Infinity = std::numeric_limits<double>::infinity();
    inline constexpr double g_Pi = std::numbers::pi;


    inline double DegreesToRadians(const double degrees)
    {
        return degrees * g_Pi / 180.0;
    }

    inline double RadiansToDegrees(const double radians)
    {
        return radians * 180.0 / g_Pi;
    }

}