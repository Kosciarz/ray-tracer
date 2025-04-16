#include <glad/gl.h>

#include "VertexBuffer.h"
#include "Utils.h"

VertexBuffer::VertexBuffer(const void* data, const std::size_t size)
{
    GLCALL(glGenBuffers(1, &m_BufferID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_BufferID));
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateData(const void* data, const std::size_t size) const
{
    Bind();
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
