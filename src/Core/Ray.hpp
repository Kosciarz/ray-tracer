#pragma once

#include <glm/vec3.hpp>

namespace raytracer {

    class Ray
    {
    public:
        Ray(const glm::vec3& origin, const glm::vec3& direction);

        glm::vec3& Origin();

        const glm::vec3& Origin() const;

        glm::vec3& Direction();

        const glm::vec3& Direction() const;

        glm::vec3 At(const double t) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_Direction;
    }

}