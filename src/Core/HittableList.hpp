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

        std::vector<std::shared_ptr<Hittable>>& Objects();
        const std::vector<std::shared_ptr<Hittable>>& Objects() const;

        std::vector<std::shared_ptr<Hittable>>::iterator begin();
        std::vector<std::shared_ptr<Hittable>>::iterator end();
        std::vector<std::shared_ptr<Hittable>>::reverse_iterator rbegin();
        std::vector<std::shared_ptr<Hittable>>::reverse_iterator rend();

        std::vector<std::shared_ptr<Hittable>>::const_iterator begin() const;
        std::vector<std::shared_ptr<Hittable>>::const_iterator end() const;
        std::vector<std::shared_ptr<Hittable>>::const_reverse_iterator rbegin() const;
        std::vector<std::shared_ptr<Hittable>>::const_reverse_iterator rend() const;

    private:
        std::vector<std::shared_ptr<Hittable>> m_Objects;
    };


    inline std::vector<std::shared_ptr<Hittable>>::iterator HittableList::begin()
    {
        return m_Objects.begin();
    }

    inline std::vector<std::shared_ptr<Hittable>>::iterator HittableList::end()
    {
        return m_Objects.end();
    }
    
    inline std::vector<std::shared_ptr<Hittable>>::reverse_iterator HittableList::rbegin()
    {
        return m_Objects.rbegin();
    }

    inline std::vector<std::shared_ptr<Hittable>>::reverse_iterator HittableList::rend()
    {
        return m_Objects.rend();
    }

    inline std::vector<std::shared_ptr<Hittable>>::const_iterator HittableList::begin() const
    {
        return m_Objects.begin();
    }

    inline std::vector<std::shared_ptr<Hittable>>::const_iterator HittableList::end() const
    {
        return m_Objects.end();
    }
    
    inline std::vector<std::shared_ptr<Hittable>>::const_reverse_iterator HittableList::rbegin() const
    {
        return m_Objects.rbegin();
    }

    inline std::vector<std::shared_ptr<Hittable>>::const_reverse_iterator HittableList::rend() const
    {
        return m_Objects.rend();
    }

}