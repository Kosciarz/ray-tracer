#pragma once

#include <filesystem>
#include <cstdint>
#include <utility>

#include "OpenGLHeaders.hpp"

#include "Utils/RayTracerUtils.hpp"

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
        static std::shared_ptr<Image> Create(std::int32_t width, std::int32_t height,
                                 ImageFormat format, const void* data, std::uint32_t unitIndex);

        static std::shared_ptr<Image> Create(const std::filesystem::path& path, std::uint32_t unitIndex);

        Image(const std::filesystem::path& path, std::uint32_t unitIndex);

        Image(std::int32_t width, std::int32_t height,
              ImageFormat format, const void* data, std::uint32_t unitIndex);

        Image() = default;

        ~Image();

        void Bind() const;

        void Unbind() const;

        void SetData(const void* data) const;

        void SetParameter(GLenum name, GLint value) const;

        [[nodiscard]] std::int32_t Width() const;

        [[nodiscard]] std::int32_t Height() const;

        [[nodiscard]] GLuint Handle() const;

    private:
        [[nodiscard]] std::pair<GLenum, GLenum> GetGLFormats() const;

    private:
        std::int32_t m_Width = 0;
        std::int32_t m_Height = 0;

        GLuint m_Handle = 0;

        GLenum m_Target = 0;
        std::uint32_t m_UnitIndex = 0;
        ImageFormat m_Format = ImageFormat::None;
    };

}