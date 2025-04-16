#include <glad/gl.h>

#include "IndexBuffer.h"
#include "Utils.h"

IndexBuffer::IndexBuffer(const void* data, std::int32_t size)
{
    GLCALL(glGenBuffers(1, &m_BufferID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_BufferID));
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
