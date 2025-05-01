#pragma once

#include <filesystem>
#include <memory>
#include <cstdint>

#include "RayTracerGL.h"

namespace raytracer {

    class Texture
    {
    public:
        static std::shared_ptr<Texture> Create(const GLenum target, const std::uint32_t unitIndex, const void* data,
            const std::int32_t m_Width, const std::int32_t height);

        static std::shared_ptr<Texture> Create(const GLenum target, const std::uint32_t unitIndex, const std::filesystem::path& path);

        Texture(const GLenum type, const std::uint32_t unitIndex, const std::filesystem::path& path);

        Texture(const GLenum type, const std::uint32_t unitIndex, const void* data,
            const std::int32_t m_Width, const std::int32_t height);

        void SetData(const void* data) const;

        Texture() = default;

        ~Texture();

        std::uint32_t GetWidth() const;

        std::uint32_t GetHeight() const;

        GLuint GetHandle() const;

        void Bind() const;

        void Unbind() const;

        void SetParameter(const GLenum pname, const GLint param) const;

    private:
        GLuint m_Handle;
        std::int32_t m_Width;
        std::int32_t m_Height;
        GLenum m_Target;
        std::uint32_t m_UnitIndex;
    };

}