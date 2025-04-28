#include <glad/gl.h>

#include "IndexBuffer.h"
#include "Utils.h"

#include <cstddef>
#include <memory>


std::shared_ptr<IndexBuffer> IndexBuffer::Create(const GLenum indexType, const std::size_t size, const void* data, const GLenum usage)
{
    return std::make_shared<IndexBuffer>(indexType, size, data, usage);
}

IndexBuffer::IndexBuffer(const GLenum indexType, const std::size_t size, const void* data, const GLenum usage)
    : m_Size{size}, m_IndexType{indexType}
{
    GL_CHECK(glGenBuffers(1, &m_BufferID));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

IndexBuffer::~IndexBuffer()
{
    GL_CHECK(glDeleteBuffers(1, &m_BufferID));
}

std::size_t IndexBuffer::Size() const
{
    return m_Size;
}

GLenum IndexBuffer::IndexType() const
{
    return m_IndexType;
}

void IndexBuffer::Bind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
}

void IndexBuffer::Unbind() const
{
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
