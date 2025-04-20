#pragma once

#include <string>
#include <random>
#include <cstdint>

class Random
{
public:
    [[nodiscard]] static std::int32_t RandomInt(const std::int32_t min, const std::int32_t max)
    {
        std::uniform_int_distribution<std::int32_t> dist{min, max};
        return dist(s_Engine);
    }

    [[nodiscard]] static double RandomDouble(const double min, const double max)
    {
        std::uniform_real_distribution<> dist{min, max};
        return dist(s_Engine);
    }

    [[nodiscard]] static bool RandomBool()
    {
        static std::bernoulli_distribution dist{0.5};
        return dist(s_Engine);
    }

    [[nodiscard]] static std::string RandomString(const std::size_t length)
    {
        static constexpr char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&";
        static constexpr auto size = sizeof(characters) - 1;
        static std::uniform_int_distribution<std::size_t> dist{0, size - 1};
        
        std::string result{};
        result.reserve(length);
        for (std::size_t i{0}; i < length; ++i)
        {
            result += characters[dist(s_Engine)];
        }
        return result;
    }

    [[nodiscard]] static char RandomChar()
    {
        static constexpr char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&";
        static constexpr auto size = sizeof(characters) - 1;
        static std::uniform_int_distribution<std::size_t> dist{0, size - 1};
        return dist(s_Engine);
    }

private:
    inline static std::random_device s_Device;
    inline static std::mt19937 s_Engine{s_Device()};
};