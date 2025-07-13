#include "Buffer.hpp"

#include <memory>

#include "OpenGLHeaders.hpp"

#include "Utils/RayTracerUtils.hpp"
#include "Utils/GLUtils.hpp"

namespace raytracer {

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, const std::size_t size)
    {
        return std::make_shared<VertexBuffer>(data, size);
    }

    VertexBuffer::VertexBuffer(const void* data, const std::size_t size)
    {
        GL_CHECK(glGenBuffers(1, &m_ID));
        Bind();
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    VertexBuffer::~VertexBuffer()
    {
        GL_CHECK(glDeleteBuffers(1, &m_ID));
    }

    void VertexBuffer::Bind() const
    {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
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


    std::shared_ptr<IndexBuffer> IndexBuffer::Create(const std::size_t size, const void* data)
    {
        return std::make_shared<IndexBuffer>(size, data);
    }

    IndexBuffer::IndexBuffer(const std::size_t size, const void* data)
        : m_Size{size}
    {
        GL_CHECK(glGenBuffers(1, &m_ID));
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
        GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer()
    {
        GL_CHECK(glDeleteBuffers(1, &m_ID));
    }

    std::size_t IndexBuffer::Size() const
    {
        return m_Size;
    }

    void IndexBuffer::Bind() const
    {
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
    }

    void IndexBuffer::Unbind() const
    {
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

}
