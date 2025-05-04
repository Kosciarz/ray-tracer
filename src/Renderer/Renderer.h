#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include <glm/vec4.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Image.h"
#include "Utils/Result.h"

namespace raytracer {

    class Renderer
    {
    public:
        Renderer() = delete;

        static void Clear(const glm::vec4& color = glm::vec4{0.0, 0.0, 0.0, 1.0});

        static void Draw(const std::shared_ptr<VertexArray>& vertexArray,
            const std::shared_ptr<Shader>& shader,
            const std::vector<std::shared_ptr<Image>>& textures = {});
    };

}