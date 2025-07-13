#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <format>
#include <string_view>

namespace raytracer {

    class Timer
    {
    public:
        using Clock = std::chrono::high_resolution_clock;

        Timer()
            : m_Start{Clock::now()}
        {
        }

        void Reset() noexcept
        {
            m_Start = Clock::now();
        }

        [[nodiscard]] double ElapsedSeconds() const noexcept
        {
            return std::chrono::duration<double>(GetTimeDifference()).count();
        }

        [[nodiscard]] double ElapsedMilliseconds() const noexcept
        {
            return std::chrono::duration<double, std::milli>(GetTimeDifference()).count();
        }

        [[nodiscard]] double ElapsedMicroseconds() const noexcept
        {
            return std::chrono::duration<double, std::micro>(GetTimeDifference()).count();
        }

        [[nodiscard]] double ElapsedNanoseconds() const noexcept
        {
            return std::chrono::duration<double, std::nano>(GetTimeDifference()).count();
        }

    private:
        Clock::duration GetTimeDifference() const noexcept
        {
            return Clock::now() - m_Start;
        }

    private:
        Clock::time_point m_Start;
    };


    class ScopedTimer
    {
    public:
        explicit ScopedTimer(const std::string_view name)
            : m_Name{name}
        {
        }

        ~ScopedTimer()
        {
            std::cout << std::format("[{}]: {}ms", m_Name, m_Timer.ElapsedMilliseconds()) << '\n';
        }

    private:
        Timer m_Timer;
        std::string m_Name;
    };

}
