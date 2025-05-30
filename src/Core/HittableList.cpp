#include "HittableList.hpp"

#include <vector>
#include <memory>

#include "Hittable.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    void HittableList::Add(const std::shared_ptr<Hittable>& object)
    {
        m_Objects.push_back(object);
    }

    void HittableList::Clear()
    {
        m_Objects.clear();
    }

    bool HittableList::Hit(const Ray& ray, const Interval& rayT, HitRecord& rec) const
    {
        HitRecord tempRec{};
        bool hitAnything = false;
        auto closestSoFar = rayT.Max();
        
        for (const auto& object : m_Objects)
        {
            if (object->Hit(ray, Interval{rayT.Min(), closestSoFar}, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

    std::vector<std::shared_ptr<Hittable>>& HittableList::Objects()
    {
        return m_Objects;
    }

    const std::vector<std::shared_ptr<Hittable>>& HittableList::Objects() const
    {
        return m_Objects;
    }

}