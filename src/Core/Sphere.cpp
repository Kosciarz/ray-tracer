#include "Sphere.hpp"

#include <iostream>

#include <glm/glm.hpp>

#include "Hittable.hpp"

namespace raytracer {

    Sphere::Sphere(const glm::vec3& center, const double radius)
        : m_Center{center}, m_Radius{radius}
    {
    }

    bool raytracer::Sphere::Hit(const Ray& ray, const Interval& rayT, HitRecord& record) const
    {
        // Calculate the vector from ray's origin to sphere's center
        auto originToCenter = m_Center - ray.Origin();

        // Solve the quadratic equation to determine if and where the ray hits the sphere
        auto a = glm::pow(glm::length(ray.Direction()), 2);
        auto h = glm::dot(ray.Direction(), originToCenter);
        auto c = glm::pow(glm::length(originToCenter), 2) - glm::pow(m_Radius, 2);

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtDisc = std::sqrt(discriminant);

        // Find the nearest root (t1 or t2) that lies in the accaptable range
        auto root = (h - sqrtDisc) / a;
        if (!rayT.Surrounds(root))
        {
            root = (h + sqrtDisc) / a;
            if (!rayT.Surrounds(root))
                return false;
        }

        record.t = root;
        record.point = ray.At(record.t);
        glm::vec3 outwardNormal = (record.point - m_Center) / static_cast<float>(m_Radius);
        record.SetFaceNormal(ray, outwardNormal);

        return true;
    }

}