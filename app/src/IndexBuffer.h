#pragma once

#include <glad/gl.h>

#include <cstdint>

class IndexBuffer
{
public:
    IndexBuffer(GLsizeiptr size, const void* data, GLenum drawType);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

private:
    std::uint32_t m_BufferID;
};
