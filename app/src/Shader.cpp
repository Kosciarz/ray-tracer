#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Utils.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    LoadSources(vertexPath, fragmentPath);
    CreateShader();
}

Shader::~Shader()
{
    GL_CHECK(glDeleteProgram(m_ProgramID));
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

std::uint32_t Shader::GetProgramID() const
{
    return m_ProgramID;
}

std::string Shader::ReadFile(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file)
        std::cerr << "failed to open shader file: " << path << '\n';

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

void Shader::LoadSources(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    m_Sources.vertex = ReadFile(vertexPath);
    m_Sources.fragment = ReadFile(fragmentPath);
}

std::uint32_t Shader::CompileShader(const GLenum shaderType, const std::string& source)
{
    const char* sourcePtr = source.c_str();
    std::uint32_t shader = glCreateShader(shaderType);
    GL_CHECK(glShaderSource(shader, 1, &sourcePtr, nullptr));
    GL_CHECK(glCompileShader(shader));

    std::int32_t success;
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


void Shader::CreateShader()
{
   std::uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, m_Sources.vertex);
   std::uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_Sources.fragment);

   m_ProgramID = glCreateProgram();
   GL_CHECK(glAttachShader(m_ProgramID, vertexShader));
   GL_CHECK(glAttachShader(m_ProgramID, fragmentShader));
   GL_CHECK(glLinkProgram(m_ProgramID));
   GL_CHECK(glValidateProgram(m_ProgramID));

   std::int32_t success;
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

