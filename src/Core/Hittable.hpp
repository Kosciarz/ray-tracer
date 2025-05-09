#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"

namespace raytracer {

    struct HitRecord
    {
        glm::vec3 point;
        glm::vec3 normal;
        double t;
    };

    class Hittable
    {
    public:
        virtual ~Hittable() = default;

        virtual bool Hit(const Ray& ray, const double tmin, const double tmax, HitRecord& record) = 0;
    };

}