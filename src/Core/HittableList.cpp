#include "HittableList.hpp"

#include <vector>

#include "Hittable.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    void HittableList::Add(const Ref<Hittable>& object)
    {
        m_Objects.push_back(object);
    }

    void HittableList::Clear()
    {
        m_Objects.clear();
    }

    bool HittableList::Hit(const Ray& ray, const double tmin, const double tmax, HitRecord& rec) const
    {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = tmax;
        
        for (const auto& object : m_Objects)
        {
            if (object->Hit(ray, tmin, closestSoFar, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

    std::vector<Ref<Hittable>>& HittableList::Objects()
    {
        return m_Objects;
    }

    const std::vector<Ref<Hittable>>& HittableList::Objects() const
    {
        return m_Objects;
    }

}