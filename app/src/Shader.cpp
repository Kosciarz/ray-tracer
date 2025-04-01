#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

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

std::string Shader::ReadFile(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error{"Error: failed to open shader file: " + path.string()};

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

void Shader::LoadSources(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    m_Sources.vertex = ReadFile(vertexPath);
    m_Sources.fragment = ReadFile(fragmentPath);
}

void Shader::CreateShader()
{
    std::uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, m_Sources.vertex);
    std::uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_Sources.fragment);

    std::uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    std::int32_t success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        char message[512];
        glGetProgramInfoLog(program, sizeof(message), nullptr, message);
        std::cerr << "Error: failed to link program: " << message << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    m_ProgramID = program;
}

std::uint32_t Shader::CompileShader(const std::uint32_t shaderType, const std::string& source)
{
    const char* sourcePtr = source.c_str();
    std::uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    std::int32_t success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        char message[512];
        glGetShaderInfoLog(shader, 512, NULL, message);
        std::cerr << "Error: failed to compile "
                  << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader" << '\n'
                  << message << '\n';
    }
    return shader;
}
