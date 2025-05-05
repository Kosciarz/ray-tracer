#pragma once

#include <glm/vec4.hpp>

#include "Ray.hpp"

namespace raytracer {

    using Color = glm::vec3;

    Color ScaleColor(const Color& pixelColor);

    Color RayColor(const Ray& ray);

}