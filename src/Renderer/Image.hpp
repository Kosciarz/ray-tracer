#pragma once

#include <filesystem>
#include <cstdint>

#include "OpenGLHeaders.hpp"

#include "Utils/Utils.hpp"

namespace raytracer {

    enum class ImageFormat : GLenum
    {
        None = 0,
        RGB = GL_RGB,
        RGBA = GL_RGBA,
    };

    class Image
    {
    public:
        static Ref<Image> Create(const std::int32_t m_Width, const std::int32_t height,
            const ImageFormat format, const void* data, const std::uint32_t unitIndex);

        static Ref<Image> Create(const std::filesystem::path& path, const std::uint32_t unitIndex);

        Image(const std::filesystem::path& path, const std::uint32_t unitIndex);

        Image(const std::int32_t m_Width, const std::int32_t height,
            const ImageFormat format, const void* data, const std::uint32_t unitIndex);

        Image() = default;

        ~Image();

        void Bind() const;

        void Unbind() const;

        void SetData(const void* data) const;

        void SetParameter(const GLenum pname, const GLint param) const;

        std::uint32_t GetWidth() const;

        std::uint32_t GetHeight() const;

        GLuint GetHandle() const;

    private:
        std::int32_t m_Width = 0;
        std::int32_t m_Height = 0;

        GLuint m_Handle;

        GLenum m_Target;
        std::uint32_t m_UnitIndex;
        ImageFormat m_Format;
    };

}