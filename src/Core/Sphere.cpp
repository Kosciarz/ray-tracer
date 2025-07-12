#include "Sphere.hpp"

#include <glm/glm.hpp>

#include "Hittable.hpp"

namespace raytracer {

    Sphere::Sphere(const glm::vec3& center, const double radius)
        : m_Center{center}, m_Radius{radius}
    {
    }

    bool Sphere::Hit(const Ray& ray, const Interval& rayT, HitRecord& record) const
    {
        // Calculate the vector from ray's origin to sphere's center
        const auto originToCenter = m_Center - ray.Origin();

        // Solve the quadratic equation to determine if and where the ray hits the sphere
        const auto a = glm::pow(glm::length(ray.Direction()), 2);
        const auto halfB = glm::dot(ray.Direction(), originToCenter);
        const auto c = glm::pow(glm::length(originToCenter), 2) - glm::pow(m_Radius, 2);

        const auto discriminant = halfB * halfB - a * c;
        if (discriminant < 0)
        {
            return false;
        }

        const auto sqrtDisc = std::sqrt(discriminant);

        // Find the nearest root (t1 or t2) that lies in the acceptable range
        auto root = (halfB - sqrtDisc) / a;
        if (!rayT.Surrounds(root))
        {
            root = (halfB + sqrtDisc) / a;
            if (!rayT.Surrounds(root))
            {
                return false;
            }
        }

        record.T = root;
        record.Point = ray.At(static_cast<float>(record.T));
        const glm::vec3 outwardNormal = (record.Point - m_Center) / static_cast<float>(m_Radius);
        record.SetFaceNormal(ray, outwardNormal);

        return true;
    }

}