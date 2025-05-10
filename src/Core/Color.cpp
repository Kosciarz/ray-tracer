#include "Color.hpp"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "Sphere.hpp"

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
        Sphere sphere{glm::vec3{0, 0, -1}, 0.5};
        auto t = HitSphere(sphere, ray);
        if (t > 0)
        {
            // Calculate the surface normal
            glm::vec3 normal = glm::normalize(ray.At(t) - glm::vec3{0, 0, -1});
            return static_cast<float>(0.5) * Color{normal.x + 1, normal.y + 1, normal.z + 1};
        }

        auto direction = glm::normalize(ray.Direction());
        auto a = static_cast<float>(0.5) * (direction.y + static_cast<float>(1.0));
        // Lerp (linear interpolation) between the white and blue color
        // Lerp(a) = (1 - a) * x + a * y
        return glm::mix(Color{1.0, 1.0, 1.0}, Color{0.5, 0.7, 1.0}, a);
    }


}