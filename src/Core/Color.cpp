#include "Color.hpp"

#include <glm/glm.hpp>

#include "HittableList.hpp"
#include "Interval.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    Color ScaleColor(const Color& pixelColor)
    {
        return Color{
            static_cast<std::uint8_t>(255 * pixelColor.r),
            static_cast<std::uint8_t>(255 * pixelColor.g),
            static_cast<std::uint8_t>(255 * pixelColor.b)
        };
    }

    Color RayColor(const Ray& ray, const HittableList& object)
    {
        if (HitRecord rec{}; object.Hit(ray, Interval{0, g_Infinity}, rec))
            return static_cast<float>(0.5) * (rec.Normal + Color{1, 1, 1});

        const auto direction = glm::normalize(ray.Direction());
        const auto a = static_cast<float>(0.5) * (direction.y + static_cast<float>(1.0));
        return glm::mix(Color{1.0, 1.0, 1.0}, Color{0.5, 0.7, 1.0}, a);
    }

}