#include "Shader.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "OpenGLHeaders.hpp"

#include "Utils/GLUtils.hpp"
#include "Utils/RayTracerUtils.hpp"
#include "Utils/Result.hpp"

#include <format>

namespace fs = std::filesystem;

namespace raytracer {

    static Result<std::string> ReadFile(const fs::path& path)
    {
        RAYTRACER_ASSERT(!path.empty(), "Shader path is empty");

        std::ifstream file(path, std::ios::in);
        if (!file)
        {
            return Result<std::string>::Err("Cannot open shader file: " + path.string());
        }

        const auto fileSize = fs::file_size(path);
        std::string contents(fileSize, 0);
        file.read(contents.data(), fileSize);
        return Result<std::string>::Ok(contents);
    }

    Result<ShaderSources> ShaderSources::Load(const ShaderPaths& paths)
    {
        auto vertex = ReadFile(paths.Vertex);
        if (!vertex)
        {
            return Result<ShaderSources>::Err("Failed to load Vertex shader: " + vertex.Error());
        }

        auto fragment = ReadFile(paths.Fragment);
        if (!fragment)
        {
            return Result<ShaderSources>::Err("Failed to load Vertex shader: " + fragment.Error());
        }

        return Result<ShaderSources>::Ok(ShaderSources{vertex.Value(), fragment.Value()});
    }


    Result<std::shared_ptr<Shader>> Shader::Create(const ShaderSources& sources)
    {
        auto vertexShader = CompileShader(GL_VERTEX_SHADER, sources.Vertex);
        if (!vertexShader)
        {
            return Result<std::shared_ptr<Shader>>::Err(vertexShader.Error());
        }

        auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, sources.Fragment);
        if (!fragmentShader)
        {
            return Result<std::shared_ptr<Shader>>::Err(fragmentShader.Error());
        }

        auto program = LinkProgram(ShaderHandles{vertexShader.Value(), fragmentShader.Value()});
        if (!program)
        {
            return Result<std::shared_ptr<Shader>>::Err(program.Error());
        }

        return Result<std::shared_ptr<Shader>>::Ok(std::make_shared<Shader>(program.Value()));
    }

    Shader::Shader(const GLuint program)
        : m_ProgramID{program}
    {
    }

    Shader::~Shader()
    {
        if (m_ProgramID)
        {
            GL_CHECK(glDeleteProgram(m_ProgramID));
        }
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

    void Shader::SetUniformBool(const std::string& name, const bool value) const
    {
        GL_CHECK(glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), static_cast<int>(value)));
    }

    void Shader::SetUniformInt(const std::string& name, const std::int32_t value) const
    {
        GL_CHECK(glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value));
    }

    void Shader::SetUniformFloat(const std::string& name, const float value) const
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