#pragma once

#include <glm/vec3.hpp>

#include "Ray.hpp"

namespace raytracer {

    using Color = glm::vec3;

    Color ScaleColor(const Color& pixelColor);

    Color RayColor(const Ray& ray);

    struct Sphere
    {
        glm::vec3 center;
        float radius;
    };

    bool HitSphere(const Sphere& sphere, const Ray& ray);

}