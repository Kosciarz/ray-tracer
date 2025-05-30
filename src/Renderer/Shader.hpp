#pragma once

#include <filesystem>
#include <string>

#include "OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    struct ShaderPaths
    {
        std::filesystem::path Vertex;
        std::filesystem::path Fragment;
    };

    struct ShaderHandles
    {
        GLuint Vertex;
        GLuint Fragment;
    };

    struct ShaderSources
    {
        std::string Vertex;
        std::string Fragment;

        static Result<ShaderSources> Load(const ShaderPaths& paths);
    };

    class Shader
    {
    public:
        static Result<std::shared_ptr<Shader>> Create(const ShaderSources& sources);

        Shader() = default;

        explicit Shader(GLuint program);

        ~Shader();

        [[nodiscard]] GLuint GetID() const;

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
        static Result<GLuint> CompileShader(GLenum shaderType, const std::string& source);

        static Result<GLuint> LinkProgram(const ShaderHandles& handles);

    private:
        GLuint m_ProgramID;
    };

}