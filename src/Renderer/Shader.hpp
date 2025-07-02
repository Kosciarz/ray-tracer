#pragma once

#include <filesystem>
#include <string>
#include <memory>

#include "OpenGLHeaders.hpp"

#include "Utils/Result.hpp"

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
    };

    class Shader
    {
    public:
        using Ptr = std::shared_ptr<Shader>;

        static Ptr Create(const ShaderPaths& paths);

        explicit Shader(const ShaderPaths& paths);
        ~Shader();

        [[nodiscard]] GLuint ID() const;

        void Use() const;
        void Unuse() const;

    private:
        static Result<ShaderSources> LoadSources(const ShaderPaths& paths);
        static Result<GLuint> CompileShader(GLenum shaderType, const std::string& source);
        static Result<GLuint> LinkProgram(const ShaderHandles& handles);

    private:
        GLuint m_ID;
    };

}