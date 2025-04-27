#include <glad/gl.h>

#include "IndexBuffer.h"
#include "Utils.h"

#include <cstddef>

IndexBuffer::IndexBuffer(std::size_t size, const void* data, GLenum usage)
{
    GL_CHECK(glGenBuffers(1, &m_BufferID));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
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
