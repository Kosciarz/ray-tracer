#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include <glm/vec4.hpp>

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "Image.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class Renderer
    {
    public:
        Renderer() = delete;

        static void Clear(const glm::vec4& color = glm::vec4{0.0, 0.0, 0.0, 1.0});

        static void Draw(const Ref<VertexArray>& vertexArray,
            const Ref<Shader>& shader,
            const std::vector<Ref<Image>>& textures = {});
    };

}