#include <glad/gl.h>

#include "VAO.h"
#include "VertexBuffer.h"
#include "Utils.h"

VAO::VAO()
{
    GL_CHECK(glGenVertexArrays(1, &m_VAO));
}

VAO::~VAO()
{
    GL_CHECK(glDeleteVertexArrays(1, &m_VAO));
}

void VAO::Bind() const
{
    GL_CHECK(glBindVertexArray(m_VAO));
}

void VAO::Unbind() const
{
    GL_CHECK(glBindVertexArray(0));
}

void VAO::AddVertexBuffer(const VertexBuffer& buffer, std::uint32_t index, std::uint32_t size, std::uint32_t type, std::int32_t stride, const void* offset) const
{
    Bind();
    buffer.Bind();
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset));
}
