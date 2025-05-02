#include "AssetManager.h"

#include <string>
#include <unordered_map>
#include <memory>

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Image.h"
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

    void AssetManager::AddImage(const std::string& name, std::shared_ptr<Image> texture)
    {
        m_Images[name] = texture;
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

    std::shared_ptr<Image>& AssetManager::GetImage(const std::string& name)
    {
        RAYTRACER_ASSERT(m_Images.contains(name), "Invalid texture name: " + name);
        return m_Images[name];
    }

}