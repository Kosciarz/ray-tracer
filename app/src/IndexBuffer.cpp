#include <glad/gl.h>

#include "IndexBuffer.h"
#include "Utils.h"

IndexBuffer::IndexBuffer(const void* data, std::int32_t size)
{
    GL_CHECK(glGenBuffers(1, &m_BufferID));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GL_CHECK(glDeleteBuffers(1, &m_BufferID));
}

void IndexBuffer::Bind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
