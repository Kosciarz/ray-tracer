#pragma once

#include <vector>
#include <type_traits>

#include "Ray.hpp"
#include "Hittable.hpp"
#include "Interval.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class HittableList
    {
    public:
        HittableList() = default;

        void Add(const Ref<Hittable>& object);

        void Clear();

        bool Hit(const Ray& ray, const Interval& rayT, HitRecord& rec) const;


        std::vector<Ref<Hittable>>& Objects();
        const std::vector<Ref<Hittable>>& Objects() const;

        std::vector<Ref<Hittable>>::iterator begin();
        std::vector<Ref<Hittable>>::iterator end();
        std::vector<Ref<Hittable>>::reverse_iterator rbegin();
        std::vector<Ref<Hittable>>::reverse_iterator rend();

        std::vector<Ref<Hittable>>::const_iterator begin() const;
        std::vector<Ref<Hittable>>::const_iterator end() const;
        std::vector<Ref<Hittable>>::const_reverse_iterator rbegin() const;
        std::vector<Ref<Hittable>>::const_reverse_iterator rend() const;

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
    
    inline std::vector<Ref<Hittable>>::reverse_iterator HittableList::rbegin()
    {
        return m_Objects.rbegin();
    }

    inline std::vector<Ref<Hittable>>::reverse_iterator HittableList::rend()
    {
        return m_Objects.rend();
    }

    inline std::vector<Ref<Hittable>>::const_iterator HittableList::begin() const
    {
        return m_Objects.begin();
    }

    inline std::vector<Ref<Hittable>>::const_iterator HittableList::end() const
    {
        return m_Objects.end();
    }
    
    inline std::vector<Ref<Hittable>>::const_reverse_iterator HittableList::rbegin() const
    {
        return m_Objects.rbegin();
    }

    inline std::vector<Ref<Hittable>>::const_reverse_iterator HittableList::rend() const
    {
        return m_Objects.rend();
    }

}