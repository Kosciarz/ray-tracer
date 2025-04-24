#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "ShaderSource.h"

#include <filesystem>
#include <string>
#include <optional>

class Shader
{
public:
    explicit Shader(const ShaderSource& source);

    Shader(const std::string& vertexSource, const std::string& fragmentSource);

    ~Shader();

    void Use() const;

    void Unuse() const;

    GLuint GetID() const;

    void SetUniformBool(const std::string& name, bool value) const;

    void SetUniformInt(const std::string& name, std::int32_t value) const;

    void SetUniformFloat(const std::string& name, float value) const;

private:
    void CreateShader(const ShaderSource& source);

    GLuint CompileShader(const GLenum shaderType, const std::string& source);

private:
    GLuint m_ID;
};
