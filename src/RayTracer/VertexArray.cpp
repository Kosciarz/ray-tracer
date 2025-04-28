#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Utils.h"

#include <glad/gl.h>

#include <memory>


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

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* offset) const
{
    vertexBuffer->Bind();
    GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
}

void VertexArray::EnableVertexAttribArray(GLuint enableArray) const 
{
    GL_CHECK(glEnableVertexAttribArray(enableArray));
}