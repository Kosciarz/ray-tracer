#include "VertexBuffer.h"

#include "RayTracerGL.h"

#include <memory>

#include "Utils.h"

namespace raytracer {

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, const std::size_t size)
    {
        return std::make_shared<VertexBuffer>(data, size);
    }

    VertexBuffer::VertexBuffer(const void* data, const std::size_t size)
    {
        GL_CHECK(glGenBuffers(1, &m_BufferID));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    VertexBuffer::~VertexBuffer()
    {
        GL_CHECK(glDeleteBuffers(1, &m_BufferID));
    }

    void VertexBuffer::Bind() const
    {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
    }

    void VertexBuffer::Unbind() const
    {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VertexBuffer::UpdateData(const void* data, const std::size_t size) const
    {
        Bind();
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    }

}