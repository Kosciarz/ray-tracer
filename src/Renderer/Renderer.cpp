#include "Renderer.hpp"

#include <string>
#include <unordered_map>
#include <vector>

#include "OpenGLHeaders.hpp"

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Image.hpp"

#include "Utils/RayTracerUtils.hpp"
#include "Utils/gl_utils.hpp"

namespace raytracer {

    void Renderer::Clear(const glm::vec4& color)
    {
        GL_CHECK(glClearColor(color.r, color.g, color.b, color.a));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Draw(const Ref<VertexArray>& vertexArray, 
        const Ref<Shader>& shader,
        const std::vector<Ref<Image>>& textures)
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

        GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer->Size(), GL_UNSIGNED_INT, nullptr));
    }

}