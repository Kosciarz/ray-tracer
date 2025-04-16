#include <glad/gl.h>

#include "VAO.h"
#include "VertexBuffer.h"
#include "Utils.h"

VAO::VAO()
{
    GLCALL(glGenVertexArrays(1, &m_VAO));
}

VAO::~VAO()
{
    GLCALL(glDeleteVertexArrays(1, &m_VAO));
}

void VAO::Bind() const
{
    GLCALL(glBindVertexArray(m_VAO));
}

void VAO::Unbind() const
{
    GLCALL(glBindVertexArray(0));
}

void VAO::AddVertexBuffer(const VertexBuffer& buffer, std::uint32_t index, std::uint32_t size, std::uint32_t type, std::int32_t stride, const void* offset) const
{
    Bind();
    buffer.Bind();
    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset));
}
