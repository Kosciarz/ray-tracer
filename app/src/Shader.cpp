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
    GLCALL(glDeleteProgram(m_ProgramID));
}

void Shader::Use() const
{
    GLCALL(glUseProgram(m_ProgramID));
}

void Shader::Unuse() const
{
    GLCALL(glUseProgram(0));
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

std::uint32_t Shader::CompileShader(const std::uint32_t shaderType, const std::string& source)
{
    const char* sourcePtr = source.c_str();
    std::uint32_t shader = glCreateShader(shaderType);
    GLCALL(glShaderSource(shader, 1, &sourcePtr, nullptr));
    GLCALL(glCompileShader(shader));

    std::int32_t success;
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (success != GL_TRUE)
    {
        char message[512];
        GLCALL(glGetShaderInfoLog(shader, 512, NULL, message));
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
   GLCALL(glAttachShader(m_ProgramID, vertexShader));
   GLCALL(glAttachShader(m_ProgramID, fragmentShader));
   GLCALL(glLinkProgram(m_ProgramID));
   GLCALL(glValidateProgram(m_ProgramID));

   std::int32_t success;
   GLCALL(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success));
   if (success != GL_TRUE)
   {
       char message[512];
       GLCALL(glGetProgramInfoLog(m_ProgramID, sizeof(message), nullptr, message));
       std::cerr << "Error: failed to link program: " << message << '\n';
   }

   GLCALL(glDeleteShader(vertexShader));
   GLCALL(glDeleteShader(fragmentShader));
}

