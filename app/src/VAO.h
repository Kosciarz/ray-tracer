#pragma once

#include "VertexBuffer.h"

#include <cstdint>

class VAO
{
public:
    VAO();

    ~VAO();

    void Bind() const;

    void Unbind() const;

    void AddVertexBuffer(const VertexBuffer& buffer, std::uint32_t index, std::uint32_t size, std::uint32_t type, std::int32_t stride, const void* offset) const;

private:
    std::uint32_t m_VAO;
};
