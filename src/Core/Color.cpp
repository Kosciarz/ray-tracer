#include "Color.hpp"

#include <glm/glm.hpp>

namespace raytracer {

    Color ScaleColor(const Color& pixelColor)
    {
        return Color{
            static_cast<std::uint8_t>(255 * pixelColor.r),
            static_cast<std::uint8_t>(255 * pixelColor.g),
            static_cast<std::uint8_t>(255 * pixelColor.b)
        };
    }

    Color RayColor(const Ray& ray)
    {
        if (HitSphere(Sphere{glm::vec3{0, 0, 1}, 0.5}, ray))
            return Color{1, 0, 0};

        auto direction = glm::normalize(ray.Direction());
        auto a = static_cast<float>(0.5) * (direction.y + static_cast<float>(1.0));
        // Lerp (linear interpolation) between the white and blue color
        // Lerp(a) = (1 - a) * x + a * y
        return (static_cast<float>(1.0) - a) * Color{1.0, 1.0, 1.0} + a * Color{0.5, 0.7, 1.0};
    }

    bool HitSphere(const Sphere& sphere, const Ray& ray)
    {
        auto oc = sphere.center - ray.Origin();

        // Quadratic equation
        auto a = glm::dot(ray.Direction(), ray.Direction());
        auto b = glm::dot(static_cast<float>(-2) * ray.Direction(), oc);
        auto c = glm::dot(oc, oc) - glm::pow(sphere.radius, 2);
        auto discrimint = glm::pow(b, 2) - 4 * a * c;

        return discrimint >= 0;
    }

}