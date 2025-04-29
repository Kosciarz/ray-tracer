#include "Renderer.h"

#include <string>
#include <unordered_map>

#include "RayTracerGL.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"

namespace raytracer {

    void Renderer::Draw()
    {
        m_VertexArray->Bind();
        m_VertexArray->GetIndexBuffer()->Bind();
        glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->Size(), m_VertexArray->GetIndexBuffer()->IndexType(), 0);
    }

    void Renderer::AddVertexArray(std::shared_ptr<VertexArray> vertexArray)
    {
        m_VertexArray = vertexArray;
    }

    void Renderer::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
    {
        m_VertexBuffer = vertexBuffer;
    }

    void Renderer::AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
    {
        m_IndexBuffer = indexBuffer;
    }

    void Renderer::AddShader(std::shared_ptr<Shader> shader)
    {
        m_Shader = shader;
    }

    void Renderer::AddTexture(const std::string& name, std::shared_ptr<Texture> texture)
    {
        m_Textures[name] = texture;
    }

    std::shared_ptr<VertexArray> Renderer::GetVertexArray()
    {
        return m_VertexArray;
    }

    std::shared_ptr<VertexBuffer> Renderer::GetVertexBuffer()
    {
        return m_VertexBuffer;
    }

    std::shared_ptr<IndexBuffer> Renderer::GetIndexBuffer()
    {
        return m_IndexBuffer;
    }

    std::shared_ptr<Shader> Renderer::GetShader()
    {
        return m_Shader;
    }

    Result<std::shared_ptr<Texture>> Renderer::GetTexture(const std::string& name)
    {
        if (!m_Textures.contains(name))
            return Result<std::shared_ptr<Texture>>::Err("No texture with name: " + name);
        return Result<std::shared_ptr<Texture>>::Ok(m_Textures[name]);
    }

}