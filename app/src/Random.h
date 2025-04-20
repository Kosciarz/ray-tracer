#pragma once

#include <string>
#include <random>
#include <cstdint>

class Random
{
public:
    [[nodiscard]] static std::int32_t RandomInt(const std::int32_t min, const std::int32_t max)
    {
        std::uniform_int_distribution<std::int32_t> s_Dist{min, max};
        return s_Dist(m_Engine);
    }

    [[nodiscard]] static std::uint32_t RandomUInt(const std::uint32_t min, const std::uint32_t max)
    {
        std::uniform_int_distribution<std::uint32_t> s_Dist{min, max};
        return s_Dist(m_Engine);
    }

    [[nodiscard]] static double RandomDouble(const double min, const double max)
    {
        std::uniform_real_distribution<> s_Dist{min, max};
        return s_Dist(m_Engine);
    }

    [[nodiscard]] static bool RandomBool()
    {
        static std::bernoulli_distribution s_Dist{0.5};
        return s_Dist(m_Engine);
    }

    [[nodiscard]] static std::string RandomString(const std::size_t length)
    {
        static constexpr char s_Sharacters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#@$%&";
        static constexpr auto s_Size = sizeof(s_Sharacters) - 1;
        static std::uniform_int_distribution<std::size_t> s_Dist{0, s_Size - 1};
        
        std::string result{};
        result.reserve(length);
        for (std::size_t i{0}; i < length; ++i)
        {
            result += s_Sharacters[s_Dist(m_Engine)];
        }
        return result;
    }

    [[nodiscard]] static char RandomChar()
    {
        static constexpr char s_Characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&";
        static constexpr auto s_Size = sizeof(s_Characters) - 1;
        static std::uniform_int_distribution<std::size_t> s_Dist{0, s_Size - 1};
        return s_Characters[s_Dist(m_Engine)];
    }

private:
    inline static std::random_device m_Device;
    inline static thread_local std::mt19937 m_Engine{m_Device()};
};