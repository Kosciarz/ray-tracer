#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
    GL_CHECK(glDeleteProgram(m_ID));
}

GLuint Shader::GetID() const
{
    return m_ID;
}

void Shader::Use() const
{
    GL_CHECK(glUseProgram(m_ID));
}

void Shader::Unuse() const
{
    GL_CHECK(glUseProgram(0));
}

void Shader::SetUniformBool(const std::string& name, bool value) const
{
    GL_CHECK(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), static_cast<int>(value)));
}

void Shader::SetUniformInt(const std::string& name, std::int32_t value) const
{
    GL_CHECK(glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value));
}

void Shader::SetUniformFloat(const std::string& name, float value) const
{
    GL_CHECK(glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value));
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
    assert(source.IsValid());

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, source.vertex.value());
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, source.fragment.value());

    m_ID = glCreateProgram();
    GL_CHECK(glAttachShader(m_ID, vertexShader));
    GL_CHECK(glAttachShader(m_ID, fragmentShader));
    GL_CHECK(glLinkProgram(m_ID));
    GL_CHECK(glValidateProgram(m_ID));

    GLint success;
    GL_CHECK(glGetProgramiv(m_ID, GL_LINK_STATUS, &success));
    if (success != GL_TRUE)
    {
        char message[512];
        GL_CHECK(glGetProgramInfoLog(m_ID, sizeof(message), nullptr, message));
        std::cerr << "Error: failed to link program: " << message << '\n';
    }

    GL_CHECK(glDeleteShader(vertexShader));
    GL_CHECK(glDeleteShader(fragmentShader));
}