#pragma once

#include "Ray.hpp"

namespace raytracer {

    struct Sphere
    {
        glm::vec3 center;
        double radius;
    };

    double HitSphere(const Sphere& sphere, const Ray& ray);

}