#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <cstdint>
#include <string>

struct ShaderSource
{
    std::string vertex;
    std::string fragment;
};

class Shader
{
public:
    Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath);

    ~Shader() { glDeleteProgram(m_ProgramID); };

    inline void Use() const { glUseProgram(m_ProgramID); }

    inline void Unuse() const { glUseProgram(0); }

    inline std::uint32_t GetProgramID() const { return m_ProgramID; }

private:
    static std::string ReadFile(const std::filesystem::path& path);

    void LoadSources(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    void CreateShader();

    std::uint32_t CompileShader(const std::uint32_t shaderType, const std::string& source);

private:
    ShaderSource m_Sources;
    std::uint32_t m_ProgramID;
};
