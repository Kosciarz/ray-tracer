#include "VertexArray.h"

#include <memory>

#include "RayTracerGL.h"

#include "Buffer.h"
#include "Utils.h"

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
        m_IndexBuffer->Bind();
    }

    void VertexArray::Unbind() const
    {
        GL_CHECK(glBindVertexArray(0));
    }

    void VertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
    {
        m_IndexBuffer = indexBuffer;
    }

    std::shared_ptr<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* offset)
    {
        Bind();
        vertexBuffer->Bind();
        GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
        GL_CHECK(glEnableVertexAttribArray(index));

        m_VertexBuffers.push_back(vertexBuffer);
    }

}