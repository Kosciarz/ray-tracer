#include "Hittable.hpp"

#include <glm/vec3.hpp>

namespace raytracer {
    
    void HitRecord::SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal)
    {
        FrontFace = glm::dot(ray.Direction(), outwardNormal) < 0;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }

}