#pragma once

#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"

namespace raytracer {

    using Color = glm::vec3;

    Color ScaleColor(const Color& pixelColor);

    Color RayColor(const Ray& ray, const HittableList& object);

}