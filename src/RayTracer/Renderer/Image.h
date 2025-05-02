#pragma once

#include <filesystem>
#include <memory>
#include <cstdint>

#include "RayTracerGL.h"

namespace raytracer {

    class Image
    {
    public:
        static std::shared_ptr<Image> Create(const GLenum target, const std::uint32_t unitIndex,
            const std::int32_t m_Width, const std::int32_t height, const void* data);

        static std::shared_ptr<Image> Create(const GLenum target, const std::uint32_t unitIndex, const std::filesystem::path& path);

        Image(const GLenum type, const std::uint32_t unitIndex, const std::filesystem::path& path);

        Image(const GLenum type, const std::uint32_t unitIndex,
            const std::int32_t m_Width, const std::int32_t height, const void* data);

        void SetData(const void* data) const;

        Image() = default;

        ~Image();

        std::uint32_t GetWidth() const;

        std::uint32_t GetHeight() const;

        GLuint GetHandle() const;

        void Bind() const;

        void Unbind() const;

        void SetParameter(const GLenum pname, const GLint param) const;

    private:
        std::int32_t m_Width;
        std::int32_t m_Height;
        GLuint m_Handle;
        GLenum m_Target;
        std::uint32_t m_UnitIndex;
    };

}