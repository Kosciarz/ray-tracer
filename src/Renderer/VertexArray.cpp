#include "VertexArray.hpp"

#include <memory>
#include <utility>

#include "OpenGLHeaders.hpp"

#include "Buffer.hpp"
#include "Utils/GLUtils.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        return std::make_shared<VertexArray>();
    }

    VertexArray::VertexArray()
    {
        GL_CHECK(glGenVertexArrays(1, &m_VAO));
    }

    VertexArray::~VertexArray()
    {
        GL_CHECK(glDeleteVertexArrays(1, &m_VAO));
    }

    void VertexArray::Bind() const
    {
        GL_CHECK(glBindVertexArray(m_VAO));
    }

    void VertexArray::Unbind() const
    {
        GL_CHECK(glBindVertexArray(0));
    }

    void VertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
    {
        m_IndexBuffer = std::move(indexBuffer);
    }

    std::shared_ptr<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer, const GLuint index, const GLint size, const GLenum type,
        const GLboolean normalized, const GLsizei stride, const void* offset)
    {
        Bind();
        buffer->Bind();
        GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
        GL_CHECK(glEnableVertexAttribArray(index));

        m_VertexBuffers.push_back(std::move(buffer));
    }

}
