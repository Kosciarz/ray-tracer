#pragma once

#include <glad/gl.h>

#include <cstdint>
#include <cstddef>

class IndexBuffer
{
public:
    IndexBuffer(std::size_t size, const void* data, GLenum usage);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

private:
    std::uint32_t m_BufferID;
};
