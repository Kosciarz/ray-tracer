#include "Image.hpp"

#include <filesystem>
#include <memory>

#include "OpenGLHeaders.hpp"
#include <stb_image.h>

#include "Utils/Utils.hpp"

namespace raytracer {

    std::shared_ptr<Image> Image::Create(const std::int32_t width, const std::int32_t height,
        const ImageFormat format, const void* data, const std::uint32_t unitIndex)
    {
        return std::make_shared<Image>(width, height, format, data, unitIndex);
    }

    std::shared_ptr<Image> Image::Create(const std::filesystem::path& path, const std::uint32_t unitIndex)
    {
        return std::make_shared<Image>(path, unitIndex);
    }

    Image::Image(const std::filesystem::path& path, const std::uint32_t unitIndex)
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_set_flip_vertically_on_load(true);

        std::int32_t nrChannels;
        std::uint8_t* textureData = stbi_load(path.string().c_str(), &m_Width, &m_Height, &nrChannels, 0);

        if (nrChannels == 3)
            m_Format = ImageFormat::RGB;
        else if (nrChannels == 4)
            m_Format = ImageFormat::RGBA;


        if (textureData)
        {
            GLenum imageFormat = static_cast<GLenum>(m_Format);
            GLenum internalFormat = GL_NONE;
            if (m_Format == ImageFormat::RGB)
                internalFormat = GL_RGB8;
            else if (m_Format == ImageFormat::RGBA)
                internalFormat = GL_RGBA8;

            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, textureData));
            GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
        }
        else
        {
            std::cerr << "Error: failed to load texture: " << path << '\n';
        }

        stbi_image_free(textureData);
    }

    Image::Image(const std::int32_t width, const std::int32_t height,
        const ImageFormat format, const void* data, const std::uint32_t unitIndex)
        : m_Width{width}, m_Height{height}, m_Format{format}, m_UnitIndex{unitIndex}
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GLenum imageFormat = static_cast<GLenum>(m_Format);
        GLenum internalFormat = GL_NONE;
        if (m_Format == ImageFormat::RGB)
            internalFormat = GL_RGB8;
        else if (m_Format == ImageFormat::RGBA)
            internalFormat = GL_RGBA8;

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
        GLenum imageFormat = static_cast<GLenum>(m_Format);
        GLenum internalFormat = GL_NONE;
        if (m_Format == ImageFormat::RGB)
            internalFormat = GL_RGB8;
        else if (m_Format == ImageFormat::RGBA)
            internalFormat = GL_RGBA8;

        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, data));
    }

    void Image::SetParameter(const GLenum pname, const GLint param) const
    {
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, pname, param));
    }

    std::uint32_t Image::GetWidth() const
    {
        return m_Width;
    }

    std::uint32_t Image::GetHeight() const
    {
        return m_Height;
    }

    GLuint Image::GetHandle() const
    {
        return m_Handle;
    }

}