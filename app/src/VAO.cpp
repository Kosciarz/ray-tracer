#include <glad/gl.h>

#include "VAO.h"
#include "VertexBuffer.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_VAO);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void VAO::Bind() const
{
    glBindVertexArray(m_VAO);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::AddVertexBuffer(const VertexBuffer& buffer, std::uint32_t index, std::uint32_t size, std::uint32_t type, std::int32_t stride, const void* offset)
{
    Bind();
    buffer.Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}
