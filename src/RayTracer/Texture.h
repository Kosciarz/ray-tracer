#pragma once

#include <glad/gl.h>

#include <filesystem>

class Texture
{
public:
    Texture(const GLenum type, const GLenum number, const std::filesystem::path& path);

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