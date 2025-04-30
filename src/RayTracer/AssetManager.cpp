#include "AssetManager.h"

#include <string>
#include <unordered_map>
#include <memory>

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Utils.h"

namespace raytracer {

    void AssetManager::AddVertexArray(const std::string& name, std::shared_ptr<VertexArray> vertexArray)
    {
        m_VertexArrays[name] = vertexArray;
    }

    void AssetManager::AddShader(const std::string& name, std::shared_ptr<Shader> shader)
    {
        m_Shaders[name] = shader;
    }

    void AssetManager::AddTexture(const std::string& name, std::shared_ptr<Texture> texture)
    {
        m_Textures[name] = texture;
    }

    std::shared_ptr<VertexArray>& AssetManager::GetVertexArray(const std::string& name)
    {
        RAYTRACER_ASSERT(m_VertexArrays.contains(name), "Invalid buffer name: " + name);
        return m_VertexArrays[name];
    }

    std::shared_ptr<Shader>& AssetManager::GetShader(const std::string& name)
    {
        RAYTRACER_ASSERT(m_Shaders.contains(name), "Invalid shader name: " + name);
        return m_Shaders[name];
    }

    std::shared_ptr<Texture>& AssetManager::GetTexture(const std::string& name)
    {
        RAYTRACER_ASSERT(m_Textures.contains(name), "Invalid textur name: " + name);
        return m_Textures[name];
    }

}