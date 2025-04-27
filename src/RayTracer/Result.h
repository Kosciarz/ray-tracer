#pragma once

#include <string>
#include <utility>

template <typename T, typename E = std::string>
class [[nodiscard]] Result
{
public:
    Result() = delete;

    static Result<T> Ok(T value)
    {
        return Result{true, std::move(value), std::string{}};
    }

    static Result<T> Err(std::string error)
    {
        return {false, T{}, std::move(error)};
    }

    bool IsOk() const
    {
        return m_Success;
    }

    bool IsErr() const
    {
        return !m_Success;
    }

    T& Value()
    {
        return m_Value;
    }

    const T& Value() const
    {
        return m_Value;
    }

    E& Error()
    {
        return m_Error;
    }

    const E& Error() const
    {
        return m_Error;
    }

    T ValueOr(T defaultValue) const
    {
        return m_Success ? m_Value : std::move(defaultValue);
    }

    explicit operator bool() const
    {
        return IsOk();
    }

private:
    Result(bool success, T value, E error)
        : m_Success{success}, m_Value{std::move(value)}, m_Error{std::move(error)}
    {
    }

    bool m_Success;
    T m_Value;
    E m_Error;
};