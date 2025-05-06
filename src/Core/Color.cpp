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
        auto direction = glm::normalize(ray.Direction());
        auto a = static_cast<float>(0.5) * (direction.y + static_cast<float>(1.0));
        //return (static_cast<float>(1.0) - a) * Color{1.0, 1.0, 1.0} + a * Color{0.5, 0.7, 1.0};
        return glm::mix(Color{1.0, 1.0, 1.0}, Color{0.5, 0.7, 1.0}, a);
    }

}