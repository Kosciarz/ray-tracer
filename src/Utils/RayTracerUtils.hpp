#pragma once

#include <numbers>
#include <limits>

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

#ifndef NDEBUG
#include <cassert>
#include <iostream>

#define RAYTRACER_ASSERT(x, msg)                         \
        do {                                            \
            if (!(x)) {                                 \
                std::cerr << "Assertion failed: "       \
                          << #x << "\nMessage: "        \
                          << msg << "\nFile: "          \
                          << __FILE__ << "\nLine: "     \
                          << __LINE__ << std::endl;     \
                assert(x);                              \
            }                                           \
        } while (0)
#else
#define RAYTRACER_ASSERT(x, msg) ((void)0)
#endif
