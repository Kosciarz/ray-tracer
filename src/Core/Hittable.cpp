#include "Hittable.hpp"

#include <glm/vec3.hpp>

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {
    
    void HitRecord::SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal)
    {
        frontFace = glm::dot(ray.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }

}