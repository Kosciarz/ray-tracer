#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include <type_traits>

namespace raytracer {

    template <typename T, typename E = std::string>
    class Result
    {
    public:
        Result() = delete;

        template <typename U>
            requires std::is_constructible_v<T, U> || std::is_convertible_v<T, U>
        static auto Ok(U&& v) noexcept -> Result
        {
            return Result{true, std::forward<U>(v), E{}};
        }

        template <typename U>
            requires std::is_constructible_v<E, U> || std::is_convertible_v<E, U>
        static auto Err(U&& e) noexcept -> Result
        {
            return Result{false, T{}, std::forward<U>(e)};
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
                throw std::runtime_error{"Attempted to access value in an Err result"};
            return m_Value;
        }

        const T& Value() const&
        {
            if (!m_Success)
                throw std::runtime_error{"Attempted to access value in an Err result"};
            return m_Value;
        }

        T&& Value() &&
        {
            if (!m_Success)
                throw std::runtime_error{"Attempted to access value in an Err result"};
            return std::move(m_Value);
        }

        E& Error() &
        {
            if (m_Success)
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return m_Error;
        }

        const E& Error() const&
        {
            if (m_Success)
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return m_Error;
        }

        E&& Error() &&
        {
            if (m_Success)
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return std::move(m_Error);
        }

        explicit operator bool() const
        {
            return IsOk();
        }

    private:
        template <typename U, typename V>
        Result(const bool success, U&& value, V&& error)
            : m_Success{success}, m_Value{std::forward<U>(value)}, m_Error{std::forward<V>(error)}
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

        template <typename U>
            requires std::is_constructible_v<E, U> || std::is_convertible_v<E, U>
        static auto Err(U&& error) noexcept -> Result
        {
            return Result{false, std::forward<U>(error)};
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
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return m_Error;
        }

        const E& Error() const&
        {
            if (m_Success)
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return m_Error;
        }

        E&& Error() &&
        {
            if (m_Success)
                throw std::runtime_error{"Attempted to access error in an Ok result"};
            return std::move(m_Error);
        }

        explicit operator bool() const
        {
            return IsOk();
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
