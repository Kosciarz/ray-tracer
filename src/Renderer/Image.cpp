#include "Image.hpp"

#include <filesystem>
#include <utility>

#include "OpenGLHeaders.hpp"
#include <stb_image.h>

#include "Utils/RayTracerUtils.hpp"
#include "Utils/GLUtils.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    std::shared_ptr<Image> Image::Create(const std::int32_t width, const std::int32_t height,
        const ImageFormat format, const void* data, const std::uint32_t unitIndex)
    {
        return std::make_shared<Image>(width, height, format, data, unitIndex);
    }

    std::shared_ptr<Image> Image::Create(const fs::path& path, const std::uint32_t unitIndex)
    {
        return std::make_shared<Image>(path, unitIndex);
    }

    Image::Image(const fs::path& path, const std::uint32_t unitIndex)
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_set_flip_vertically_on_load(true);

        std::int32_t nrChannels = 0;
        std::uint8_t* textureData = stbi_load(path.string().c_str(), &m_Width, &m_Height, &nrChannels, 0);
        if (!textureData)
        {
            throw std::runtime_error{"Failed to load texture with path: " + path.string()};
        }

        switch (nrChannels) {
        case 3:
            m_Format = ImageFormat::RGB;
            break;
        case 4:
            m_Format = ImageFormat::RGBA;
            break;
        default:
            throw std::runtime_error{"Error: Unsupported number of channels: " + std::to_string(nrChannels)};
        }

        const auto [imageFormat, internalFormat] = GetGLFormats();
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, textureData));
        GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

        stbi_image_free(textureData);
        Unbind();
    }

    Image::Image(const std::int32_t width, const std::int32_t height,
        const ImageFormat format, const void* data, const std::uint32_t unitIndex)
        : m_Width{width}, m_Height{height}, m_UnitIndex{unitIndex}, m_Format{format}
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        auto [imageFormat, internalFormat] = GetGLFormats();
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, data));
    }

    Image::~Image()
    {
        GL_CHECK(glDeleteTextures(1, &m_Handle));
    }

    void Image::Bind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_Handle));
    }

    void Image::Unbind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Image::SetData(const void* data) const
    {
        Bind();
        auto [imageFormat, _] = GetGLFormats();
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, imageFormat, GL_UNSIGNED_BYTE, data));
    }

    void Image::SetParameter(const GLenum name, const GLint value) const
    {
        Bind();
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, name, value));
    }

    std::int32_t Image::Width() const
    {
        return m_Width;
    }

    std::int32_t Image::Height() const
    {
        return m_Height;
    }

    GLuint Image::Handle() const
    {
        return m_Handle;
    }

    std::pair<GLenum, GLenum> Image::GetGLFormats() const
    {
        switch (m_Format)
        {
        case ImageFormat::RGB:
            return {GL_RGB, GL_RGB8};
        case ImageFormat::RGBA:
            return {GL_RGBA, GL_RGBA8};
        default:
            RAYTRACER_ASSERT(false, "Unsupported ImageFormat");
            return {GL_NONE, GL_NONE};
        }
    }

}
