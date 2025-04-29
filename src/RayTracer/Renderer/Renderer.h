#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Result.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace raytracer {

    class Renderer
    {
    public:
        Renderer() = default;

        void Draw();

        void AddVertexArray(std::shared_ptr<VertexArray> vertexArray);

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);

        void AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

        void AddShader(std::shared_ptr<Shader> shader);

        void AddTexture(const std::string& name, std::shared_ptr<Texture> texture);

        std::shared_ptr<VertexArray> GetVertexArray();

        std::shared_ptr<VertexBuffer> GetVertexBuffer();

        std::shared_ptr<IndexBuffer> GetIndexBuffer();

        std::shared_ptr<Shader> GetShader();

        Result<std::shared_ptr<Texture>> GetTexture(const std::string& name);

    private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<Shader> m_Shader;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };

}