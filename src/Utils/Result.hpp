#pragma once

#include <string>
#include <utility>
#include <stdexcept>

namespace raytracer {

    template <typename T, typename E = std::string>
    class Result
    {
    public:
        Result() = delete;

        static Result<T> Ok(T value)
        {
            return Result{true, std::move(value), E{}};
        }

        static Result<T> Err(E error)
        {
            return {false, T{}, std::move(error)};
        }

        [[nodiscard]] bool IsOk() const
        {
            return m_Success;
        }

        [[nodiscard]] bool IsErr() const
        {
            return !m_Success;
        }

        T& Value() &
        {
            if (!m_Success)
            {
                throw std::runtime_error{"Attempted to access value in an Err result"};
            }
            return m_Value;
        }

        const T& Value() const&
        {
            if (!m_Success)
            {
                throw std::runtime_error{"Attempted to access value in an Err result"};
            }
            return m_Value;
        }

        T&& Value() &&
        {
            if (!m_Success)
            {
                throw std::runtime_error{"Attempted to access value in an Err result"};
            }
            return std::move(m_Value);
        }

        E& Error() &
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return m_Error;
        }

        const E& Error() const&
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return m_Error;
        }

        E&& Error() &&
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return std::move(m_Error);
        }

        explicit operator bool() const
        {
            return m_Success;
        }

    private:
        Result(const bool success, T value, E error)
            : m_Success{success}, m_Value{std::move(value)}, m_Error{std::move(error)}
        {
        }

        bool m_Success;
        T m_Value;
        E m_Error;
    };


    template <typename E>
    class Result<void, E>
    {
    public:
        Result() = delete;

        static Result Ok()
        {
            return Result{true, E{}};
        }

        static Result Err(std::string error)
        {
            return {false, std::move(error)};
        }

        [[nodiscard]] bool IsOk() const
        {
            return m_Success;
        }

        [[nodiscard]] bool IsErr() const
        {
            return !m_Success;
        }

        E& Error() &
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return m_Error;
        }

        const E& Error() const&
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return m_Error;
        }

        E&& Error() &&
        {
            if (m_Success)
            {
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            }
            return std::move(m_Error);
        }

        explicit operator bool() const
        {
            return m_Success;
        }

    private:
        Result(const bool success, E error)
            : m_Success{success}, m_Error{std::move(error)}
        {
        }

        bool m_Success;
        E m_Error;
    };

}