#include "Texture.h"

#include <filesystem>
#include <memory>

#include "RayTracerGL.h"
#include <stb_image.h>

#include "Utils.h"

namespace raytracer {

    std::shared_ptr<Texture> Texture::Create(const GLenum type, const std::uint32_t unitIndex, const void* data, 
        const std::int32_t m_Width, const std::int32_t height)
    {
        return std::make_shared<Texture>(type, unitIndex, data, m_Width, height);
    }

    std::shared_ptr<Texture> Texture::Create(const GLenum type, const std::uint32_t number, const std::filesystem::path& path)
    {
        return std::make_shared<Texture>(type, number, path);
    }

    void Texture::SetData(const void* data) const
    {
        Bind();
        GL_CHECK(glTexImage2D(m_Target, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    }

    Texture::Texture(const GLenum type, const std::uint32_t number, const std::filesystem::path& path)
        : m_Target{type}, m_UnitIndex{number}
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_set_flip_vertically_on_load(true);

        std::int32_t nrChannels;
        std::uint8_t* textureData = stbi_load(path.string().c_str(), &m_Width, &m_Height, &nrChannels, 0);

        GLenum format = GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;


        if (textureData)
        {
            GL_CHECK(glTexImage2D(m_Target, 0, GL_RGBA, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, textureData));
            GL_CHECK(glGenerateMipmap(m_Target));
        }
        else
        {
            std::cerr << "Error: failed to load texture: " << path << '\n';
        }

        stbi_image_free(textureData);
    }

    Texture::Texture(const GLenum type, const std::uint32_t unitIndex, const void* data, 
        const std::int32_t m_Width, const std::int32_t height)
        : m_Target{type}, m_Width{m_Width}, m_Height{height}, m_UnitIndex{unitIndex}
    {
        GL_CHECK(glGenTextures(1, &m_Handle));
        Bind();

        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glTexImage2D(m_Target, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    }

    Texture::~Texture()
    {
        GL_CHECK(glDeleteTextures(1, &m_Handle));
    }

    std::uint32_t Texture::GetWidth() const
    {
        return m_Width;
    }

    std::uint32_t Texture::GetHeight() const
    {
        return m_Height;
    }

    GLuint Texture::GetHandle() const
    {
        return m_Handle;
    }

    void Texture::Bind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(m_Target, m_Handle));
    }

    void Texture::Unbind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(m_Target, 0));
    }

    void Texture::SetParameter(const GLenum pname, const GLint param) const
    {
        GL_CHECK(glBindTexture(m_Target, m_Handle));
        GL_CHECK(glTexParameteri(m_Target, pname, param));
    }

}