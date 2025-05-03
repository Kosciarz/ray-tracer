#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <format>

namespace raytracer {

    class [[nodiscard]] Timer
    {
    public:
        using Clock = std::chrono::high_resolution_clock;

    public:
        Timer()
            : m_Start{Clock::now()}
        {
        }

        void Reset() noexcept
        {
            m_Start = Clock::now();
        }

        double GetSeconds() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::seconds>(GetTimeDifference()).count();
        }

        long long GetMilliseconds() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(GetTimeDifference()).count();
        }

        long long GetMicroseconds() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(GetTimeDifference()).count();
        }

        long long GetNanoseconds() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(GetTimeDifference()).count();
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
        ScopedTimer(const std::string& name)
            : m_Name{name}
        {
        }

        ~ScopedTimer()
        {
            std::cout << std::format("[{}]: {}ms", m_Name, m_Timer.GetMilliseconds()) << '\n';
        }

    private:
        Timer m_Timer;
        std::string m_Name;
    };

}