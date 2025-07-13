#pragma once

#include <vector>
#include <memory>

#include "Ray.hpp"
#include "Hittable.hpp"
#include "Interval.hpp"

namespace raytracer {

    class HittableList
    {
    public:
        HittableList() = default;

        void Add(const std::shared_ptr<Hittable>& object);
        void Clear();

        bool Hit(const Ray& ray, const Interval& rayT, HitRecord& rec) const;

        private:
        std::vector<std::shared_ptr<Hittable>> m_Objects;
    };

}
