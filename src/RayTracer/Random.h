#pragma once

#include <string>
#include <random>
#include <cstdint>

namespace raytracer {

    class Random
    {
    public:
        static std::int32_t RandomInt(const std::int32_t min, const std::int32_t max) noexcept
        {
            std::uniform_int_distribution<std::int32_t> dist{min, max};
            return dist(m_Engine);
        }

        static double RandomDouble(const double min, const double max)
        {
            std::uniform_real_distribution<double> dist{min, max};
            return dist(m_Engine);
        }

        static bool RandomBool()
        {
            static std::bernoulli_distribution dist{0.5};
            return dist(m_Engine);
        }

        static char RandomChar()
        {
            static constexpr char s_Characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*";
            static constexpr auto s_Size = sizeof(s_Characters) - 1;
            std::uniform_int_distribution<std::uint32_t> dist{0, s_Size - 1};
            return s_Characters[dist(m_Engine)];
        }

        static std::string RandomString(const std::size_t length)
        {
            static constexpr char s_Characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*";
            static constexpr auto s_Size = sizeof(s_Characters) - 1;
            static std::uniform_int_distribution<std::size_t> dist{0, s_Size - 1};

            std::string result(length, 0);
            for (auto& ch : result)
                ch = s_Characters[dist(m_Engine)];
            return result;
        }

    private:
        inline static std::random_device m_Device;
        inline static std::mt19937 m_Engine{m_Device()};
    };

}