#pragma once

#include <glad/gl.h>

#include <cstdint>
#include <cstddef>
#include <memory>


class IndexBuffer
{
public:
    static std::shared_ptr<IndexBuffer> Create(const GLenum indexType, const std::size_t size, const void* data, const GLenum usage);

    IndexBuffer() = default;

    IndexBuffer(const GLenum indexType, const std::size_t size, const void* data, const GLenum usage);

    ~IndexBuffer();

    std::size_t Size() const;

    GLenum IndexType() const;

    void Bind() const;

    void Unbind() const;

private:
    GLuint m_BufferID;
    std::size_t m_Size;
    GLenum m_IndexType;
};
