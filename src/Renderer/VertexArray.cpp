#include "VertexArray.hpp"

#include <memory>

#include "OpenGLHeaders.hpp"

#include "Buffer.hpp"
#include "Utils/GLUtils.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    Ref<VertexArray> VertexArray::Create()
    {
        return MakeRef<VertexArray>();
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

    void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer)
    {
        m_IndexBuffer = indexBuffer;
    }

    Ref<IndexBuffer> VertexArray::GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }

    void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer, GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* offset)
    {
        Bind();
        vertexBuffer->Bind();
        GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
        GL_CHECK(glEnableVertexAttribArray(index));

        m_VertexBuffers.push_back(vertexBuffer);
    }

}