#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Utils.h"
#include "ShaderSource.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <cassert>

namespace fs = std::filesystem;

Shader::Shader(const ShaderSource& source)
{
    CreateShader(source);
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
    CreateShader(ShaderSource{vertexSource, fragmentSource});
}

Shader::~Shader()
{
    GL_CHECK(glDeleteProgram(m_ProgramID));
}

GLuint Shader::GetID() const
{
    return m_ProgramID;
}

void Shader::Use() const
{
    GL_CHECK(glUseProgram(m_ProgramID));
}

void Shader::Unuse() const
{
    GL_CHECK(glUseProgram(0));
}

void Shader::SetUniformBool(const std::string& name, bool value) const
{
    GL_CHECK(glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), static_cast<int>(value)));
}

void Shader::SetUniformInt(const std::string& name, std::int32_t value) const
{
    GL_CHECK(glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value));
}

void Shader::SetUniformFloat(const std::string& name, float value) const
{
    GL_CHECK(glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value));
}

void Shader::SetUniformVec3(const std::string& name, const GLfloat* value) const
{
    GL_CHECK(glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, value));
}

void Shader::SetUniformVec4(const std::string& name, const GLfloat* value) const
{
    GL_CHECK(glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, value));
}

void Shader::SetUniformMat3(const std::string& name, const GLfloat* value) const
{
    GL_CHECK(glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, value));
}

void Shader::SetUniformMat4(const std::string& name, const GLfloat* value) const
{
    GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, value));
}

GLuint Shader::CompileShader(const GLenum shaderType, const std::string& source)
{
    const char* sourcePtr = source.c_str();
    GLuint shader = glCreateShader(shaderType);
    GL_CHECK(glShaderSource(shader, 1, &sourcePtr, nullptr));
    GL_CHECK(glCompileShader(shader));

    GLint success;
    GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (success != GL_TRUE)
    {
        char message[512];
        GL_CHECK(glGetShaderInfoLog(shader, 512, NULL, message));
        std::cerr << "Error: failed to compile "
            << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader" << '\n'
            << message << '\n';
    }
    return shader;
}

void Shader::CreateShader(const ShaderSource& source)
{
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, source.vertex);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, source.fragment);

    m_ProgramID = glCreateProgram();
    GL_CHECK(glAttachShader(m_ProgramID, vertexShader));
    GL_CHECK(glAttachShader(m_ProgramID, fragmentShader));
    GL_CHECK(glLinkProgram(m_ProgramID));
    GL_CHECK(glValidateProgram(m_ProgramID));

    GLint success;
    GL_CHECK(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success));
    if (success != GL_TRUE)
    {
        char message[512];
        GL_CHECK(glGetProgramInfoLog(m_ProgramID, sizeof(message), nullptr, message));
        std::cerr << "Error: failed to link program: " << message << '\n';
    }

    GL_CHECK(glDeleteShader(vertexShader));
    GL_CHECK(glDeleteShader(fragmentShader));
}