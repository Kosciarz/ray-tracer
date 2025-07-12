#include "Shader.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <format>

#include "OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/GLUtils.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    static Result<std::string> ReadFile(const fs::path& path)
    {
        RAYTRACER_ASSERT(!path.empty(), "Path is empty");

        std::ifstream file(path, std::ios::in);
        if (!file)
            return Result<std::string>::Err("Cannot open file: " + path.string());

        const auto size = fs::file_size(path);
        std::string contents(size, 0);
        file.read(contents.data(), size);
        return Result<std::string>::Ok(contents);
    }

    Result<ShaderSources> Shader::LoadSources(const ShaderPaths& paths)
    {
        auto vertex = ReadFile(paths.Vertex);
        if (!vertex)
            return Result<ShaderSources>::Err("Failed to load Vertex shader: " + vertex.Error());

        auto fragment = ReadFile(paths.Fragment);
        if (!fragment)
            return Result<ShaderSources>::Err("Failed to load Vertex shader: " + fragment.Error());

        return Result<ShaderSources>::Ok(ShaderSources{vertex.Value(), fragment.Value()});
    }

    Shader::Ptr Shader::Create(const ShaderPaths& paths)
    {
        return std::make_shared<Shader>(paths);
    }

    Shader::Shader(const ShaderPaths& paths)
    {
        auto sourcesResult = LoadSources(paths);
        if (!sourcesResult)
            throw std::runtime_error{sourcesResult.Error()};
        const auto& sources = sourcesResult.Value();

        auto vertexShader = CompileShader(GL_VERTEX_SHADER, sources.Vertex);
        if (!vertexShader)
            throw std::runtime_error{vertexShader.Error()};

        auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, sources.Fragment);
        if (!fragmentShader)
            throw std::runtime_error{fragmentShader.Error()};

        auto program = LinkProgram(ShaderHandles{vertexShader.Value(), fragmentShader.Value()});
        if (!program)
            throw std::runtime_error{program.Error()};
        
        m_ID = program.Value();
    }

    Shader::~Shader()
    {
        if (m_ID)
            GL_CHECK(glDeleteProgram(m_ID));
    }

    GLuint Shader::ID() const
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

    Result<GLuint> Shader::CompileShader(const GLenum shaderType, const std::string& source)
    {
        RAYTRACER_ASSERT(!source.empty(), "Shader source is empty");

        const char* sourcePtr = source.c_str();
        const GLuint shader = glCreateShader(shaderType);
        GL_CHECK(glShaderSource(shader, 1, &sourcePtr, nullptr));
        GL_CHECK(glCompileShader(shader));

        GLint success;
        GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
        if (success != GL_TRUE)
        {
            GLint logLength{0};
            GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));
            std::vector<char> log(logLength);
            GL_CHECK(glGetShaderInfoLog(shader, logLength, &logLength, log.data()));

            return Result<GLuint>::Err(std::format("Failed to compile {} shader: {}",
                shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                log.data()));
        }

        return Result<GLuint>::Ok(shader);
    }

    Result<GLuint> Shader::LinkProgram(const ShaderHandles& handles)
    {
        const auto program = glCreateProgram();
        GL_CHECK(glAttachShader(program, handles.Vertex));
        GL_CHECK(glAttachShader(program, handles.Fragment));
        GL_CHECK(glLinkProgram(program));
        GL_CHECK(glValidateProgram(program));

        GLint success;
        GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &success));
        if (success != GL_TRUE)
        {
            GLint logLength{0};
            GL_CHECK(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));
            std::vector<char> log(logLength);
            GL_CHECK(glGetProgramInfoLog(program, logLength, &logLength, log.data()));

            GL_CHECK(glDeleteShader(handles.Vertex));
            GL_CHECK(glDeleteShader(handles.Fragment));

            return Result<GLuint>::Err("FFailed to link program: " + std::string{log.data()});
        }

        GL_CHECK(glDeleteShader(handles.Vertex));
        GL_CHECK(glDeleteShader(handles.Fragment));

        return Result<GLuint>::Ok(program);
    }

}