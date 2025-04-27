#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Utils.h"

#include <glad/gl.h>


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

void VertexArray::AddVertexBuffer(const VertexBuffer& buffer, GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* offset) const
{
    buffer.Bind();
    GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
}

void VertexArray::EnableVertexAttribArray(GLuint enableArray) const 
{
    GL_CHECK(glEnableVertexAttribArray(enableArray));
}