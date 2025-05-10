#include "Sphere.hpp"

#include <iostream>

#include <glm/glm.hpp>

namespace raytracer {

    double HitSphere(const Sphere& sphere, const Ray& ray)
    {
        // Calculate the vector from ray's origin to sphere's center
        auto originToCenter = sphere.center - ray.Origin();

        // Solve the quadratic equation to determine if and where the ray hits the sphere
        auto a = glm::dot(ray.Direction(), ray.Direction());
        auto b = -2.0 * glm::dot(ray.Direction(), originToCenter);
        auto c = glm::dot(originToCenter, originToCenter) - glm::pow(sphere.radius, 2);
        auto discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return -1.0;
        else
            return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }

}