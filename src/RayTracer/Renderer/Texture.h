#pragma once

#include <filesystem>
#include <memory>

#include "RayTracerGL.h"

namespace raytracer {

    class Texture
    {
    public:
        static std::shared_ptr<Texture> Create(const GLenum type, const GLenum number, const std::filesystem::path& path);

        Texture(const GLenum type, const GLenum number, const std::filesystem::path& path);

        Texture() = default;

        ~Texture();

        GLuint GetID() const;

        void Bind() const;

        void Unbind() const;

        void SetParameter(const GLenum pname, const GLint param) const;

    private:
        GLuint m_TextureID;
        GLenum m_Type;
        GLenum m_Number;
    };

}