#pragma once

#include <glad/gl.h>

#include <cstdint>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, const std::size_t size);

    ~VertexBuffer();

    void Bind() const;

    void Unbind() const;

    void UpdateData(const void* data, const std::size_t size);

private:
    std::uint32_t m_BufferID;
};
