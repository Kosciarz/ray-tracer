#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

namespace raytracer {

    class AssetManager
    {
    public:
        AssetManager() = default;

        void AddVertexArray(const std::string& name, std::shared_ptr<VertexArray> vertexArray);

        void AddShader(const std::string& name, std::shared_ptr<Shader> shader);

        void AddTexture(const std::string& name, std::shared_ptr<Texture> texture);

        std::shared_ptr<VertexArray>& GetVertexArray(const std::string& name);

        std::shared_ptr<Shader>& GetShader(const std::string& name);

        std::shared_ptr<Texture>& GetTexture(const std::string& name);

    private:
        std::unordered_map<std::string, std::shared_ptr<VertexArray>> m_VertexArrays;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };

}