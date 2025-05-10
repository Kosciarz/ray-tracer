#pragma once

#include <vector>
#include <type_traits>

#include "Ray.hpp"
#include "Hittable.hpp"
#include "Utils/Utils.hpp"

namespace raytracer {

    class HittableList
    {
    public:
        HittableList() = default;

        void Add(const Ref<Hittable>& object);

        void Clear();

        bool Hit(const Ray& ray, const double tmin, const double tmax, HitRecord& rec) const;


        std::vector<Ref<Hittable>>& Objects();
        const std::vector<Ref<Hittable>>& Objects() const;

        std::vector<Ref<Hittable>>::iterator begin();
        std::vector<Ref<Hittable>>::iterator end();

        std::vector<Ref<Hittable>>::const_iterator begin() const;
        std::vector<Ref<Hittable>>::const_iterator end() const;

    private:
        std::vector<Ref<Hittable>> m_Objects;
    };


    inline std::vector<Ref<Hittable>>::iterator HittableList::begin()
    {
        return m_Objects.begin();
    }

    inline std::vector<Ref<Hittable>>::iterator HittableList::end()
    {
        return m_Objects.end();
    }

    inline std::vector<Ref<Hittable>>::const_iterator HittableList::begin() const
    {
        return m_Objects.begin();
    }

    inline std::vector<Ref<Hittable>>::const_iterator HittableList::end() const
    {
        return m_Objects.end();
    }

}