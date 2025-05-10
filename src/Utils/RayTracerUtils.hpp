#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include <numbers>
#include <limits>

namespace raytracer {

    // Constants
    inline constexpr double g_Infinity = std::numeric_limits<double>::infinity();
    inline constexpr double g_Pi = std::numbers::pi;


    // Utility functions
    inline double DegreesToRadians(const double degrees)
    {
        return degrees * g_Pi / 180.0;
    }

    inline double RadiansToDegrees(const double radians)
    {
        return radians * 180.0 / g_Pi;
    }


    // Smart pointer utilities
    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename ...Args>
    Ref<T> MakeRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename ...Args>
    Scope<T> MakeScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

}

#ifndef NDEBUG
#include <cassert>

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