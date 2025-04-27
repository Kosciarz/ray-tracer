#pragma once

#include "VertexBuffer.h"

#include <glad/gl.h>

#include <cstdint>

class VertexArray
{
public:
    VertexArray();

    ~VertexArray();

    void Bind() const;

    void Unbind() const;

    void AddVertexBuffer(const VertexBuffer& buffer, GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* offset) const;

    void EnableVertexAttribArray(GLuint enableArray) const;

private:
    std::uint32_t m_VAO;
};
