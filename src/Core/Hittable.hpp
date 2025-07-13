#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"
#include "Interval.hpp"

namespace raytracer {

    struct HitRecord
    {
        glm::vec3 Point;
        glm::vec3 Normal;
        double T;
        bool FrontFace;

        void SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal);
    };

    class Hittable
    {
    public:
        virtual ~Hittable() = default;

        virtual bool Hit(const Ray& ray, const Interval& rayT, HitRecord& record) const = 0;
    };

}
