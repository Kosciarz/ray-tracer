#pragma once

#include <random>
#include <limits>

#include <glm/vec3.hpp>

namespace raytracer {

    class Random
    {
    public:
        static void Seed(const std::uint32_t seed)
        {
            s_Generator.seed(seed);
        }

        static std::uint8_t UInt8() noexcept
        {
            thread_local std::uniform_int_distribution<std::uint16_t> dist{0, 255};
            return static_cast<std::uint8_t>(dist(s_Generator));
        }

        static std::int32_t Int() noexcept
        {
            thread_local std::uniform_int_distribution dist{
                std::numeric_limits<std::int32_t>::min(),
                std::numeric_limits<std::int32_t>::max()
            };
            return dist(s_Generator);
        }

        static std::int32_t Int(const std::int32_t min, const std::int32_t max) noexcept
        {
            std::uniform_int_distribution dist{min, max};
            return dist(s_Generator);
        }

        static std::int32_t UInt()
        {
            thread_local std::uniform_int_distribution dist{
                std::numeric_limits<std::uint32_t>::min(),
                std::numeric_limits<std::uint32_t>::max()
            };
            return dist(s_Generator);
        }

        static std::int32_t UInt(const std::uint32_t min, const std::uint32_t max) noexcept
        {
            std::uniform_int_distribution dist{min, max};
            return dist(s_Generator);
        }

        static float Float() noexcept
        {
            thread_local std::uniform_real_distribution dist{0.0f, 1.0f};
            return dist(s_Generator);
        }

        static float Float(const float min, const float max) noexcept
        {
            std::uniform_real_distribution dist{min, max};
            return dist(s_Generator);
        }

        static glm::vec3 Vec3() noexcept
        {
            return glm::vec3{Float(), Float(), Float()};
        }

        static glm::vec3 Vec3(const float min, const float max) noexcept
        {
            return glm::vec3{Float(min, max), Float(min, max), Float(min, max)};
        }

    private:
        inline thread_local static std::mt19937 s_Generator{std::random_device{}()};
    };

}