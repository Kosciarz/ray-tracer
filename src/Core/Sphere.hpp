#pragma once

#include <glm/vec3.hpp>

#include "Hittable.hpp"
#include "Ray.hpp"

namespace raytracer {

    class Sphere : public Hittable
    {
    public:
        Sphere(const glm::vec3& center, const double radius);

        bool Hit(const Ray& ray, const Interval& rayT, HitRecord& record) const override;

    private:
        glm::vec3 m_Center;
        double m_Radius;
    };

}