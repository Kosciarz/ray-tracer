#include <glad/gl.h>

#include "VAO.h"
#include "VertexBuffer.h"
#include "Utils.h"

VAO::VAO()
{
    GL_CHECK(glGenVertexArrays(1, &m_VAO));
}

VAO::~VAO()
{
    GL_CHECK(glDeleteVertexArrays(1, &m_VAO));
}

void VAO::Bind() const
{
    GL_CHECK(glBindVertexArray(m_VAO));
}

void VAO::Unbind() const
{
    GL_CHECK(glBindVertexArray(0));
}

void VAO::AddVertexBuffer(const VertexBuffer& buffer, GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* offset) const
{
    buffer.Bind();
    GL_CHECK(glVertexAttribPointer(index, size, type, normalized, stride, offset));
}

void VAO::EnableVertexAttribArray(GLuint enableArray) const 
{
    GL_CHECK(glEnableVertexAttribArray(enableArray));
}
