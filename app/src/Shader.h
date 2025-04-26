#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ShaderSource.h"
#include "Result.h"

#include <filesystem>
#include <string>
#include <optional>
#include <memory>

class Shader
{
public:
    using ShaderPtr = std::shared_ptr<Shader>;

    static Result<ShaderPtr> Create(const ShaderSources& sources);

    Shader() = default;

    explicit Shader(const GLuint program);

    ~Shader();
    
    GLuint GetID() const;

    void Use() const;

    void Unuse() const;

    void SetUniformBool(const std::string& name, bool value) const;

    void SetUniformInt(const std::string& name, std::int32_t value) const;

    void SetUniformFloat(const std::string& name, float value) const;

    void SetUniformVec3(const std::string& name, const GLfloat* value) const;

    void SetUniformVec4(const std::string& name, const GLfloat* value) const;

    void SetUniformMat3(const std::string& name, const GLfloat* value) const;

    void SetUniformMat4(const std::string& name, const GLfloat* value) const;

private:
    static Result<GLuint> CompileShader(const GLenum shaderType, const std::string& source);

    static Result<GLuint> LinkProgram(const GLuint vertexShader, const GLuint fragmentShader);

private:
    GLuint m_ProgramID;
};
