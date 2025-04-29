#include "Renderer.h"

#include <string>
#include <unordered_map>
#include <vector>

#include "RayTracerGL.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"
#include "Utils.h"

namespace raytracer {

    void Renderer::Clear(const glm::vec4& color)
    {
        GL_CHECK(glClearColor(color.x, color.y, color.z, color.w));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Draw(const std::shared_ptr<VertexArray>& vertexArray, 
        const std::shared_ptr<Shader>& shader,
        const std::vector<std::shared_ptr<Texture>>& textures,
        const GLenum drawMode)
    {
        RAYTRACER_ASSERT(vertexArray, "Vertex Array is a nullptr");
        auto indexBuffer = vertexArray->GetIndexBuffer();
        RAYTRACER_ASSERT(indexBuffer, "Index Buffer is a nullptr");
        RAYTRACER_ASSERT(shader, "Shader is a nullptr");

        shader->Use();
        for (const auto& texture : textures)
            if (texture)
                texture->Bind();

        vertexArray->Bind();
        indexBuffer->Bind();

        glDrawElements(drawMode, indexBuffer->Size(), indexBuffer->IndexType(), nullptr);
    }

}