#include "Texture.h"

#include <filesystem>
#include <memory>

#include "RayTracerGL.h"
#include <stb_image.h>

#include "Utils.h"

namespace raytracer {

    std::shared_ptr<Texture> Texture::Create(const GLenum type, const std::uint32_t number, const std::filesystem::path& path)
    {
        return std::make_shared<Texture>(type, number, path);
    }

    Texture::Texture(const GLenum type, const std::uint32_t number, const std::filesystem::path& path)
        : m_Type{type}, m_UnitIndex{number}
    {
        GL_CHECK(glGenTextures(1, &m_TextureID));
        Bind();

        GL_CHECK(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_set_flip_vertically_on_load(true);

        std::int32_t width, height, nrChannels;
        std::uint8_t* textureData = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

        GLenum format = GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;


        if (textureData)
        {
            GL_CHECK(glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, textureData));
            GL_CHECK(glGenerateMipmap(type));
        }
        else
        {
            std::cerr << "Error: failed to load texture: " << path << '\n';
        }

        stbi_image_free(textureData);
    }

    Texture::~Texture()
    {
        GL_CHECK(glDeleteTextures(1, &m_TextureID));
    }

    GLuint Texture::GetID() const
    {
        return m_TextureID;
    }

    void Texture::Bind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(m_Type, m_TextureID));
    }

    void Texture::Unbind() const
    {
        GL_CHECK(glActiveTexture(GL_TEXTURE0 + m_UnitIndex));
        GL_CHECK(glBindTexture(m_Type, 0));
    }

    void Texture::SetParameter(const GLenum pname, const GLint param) const
    {
        GL_CHECK(glBindTexture(m_Type, m_TextureID));
        GL_CHECK(glTexParameteri(m_Type, pname, param));
    }

}