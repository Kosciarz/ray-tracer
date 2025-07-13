#pragma once

#include <glm/vec3.hpp>

namespace raytracer {

    class Ray
    {
    public:
        Ray() = default;

        Ray(const glm::vec3& origin, const glm::vec3& direction);

        glm::vec3& Origin();

        [[nodiscard]] const glm::vec3& Origin() const;

        glm::vec3& Direction();

        [[nodiscard]] const glm::vec3& Direction() const;

        [[nodiscard]] glm::vec3 At(float t) const;

    private:
        glm::vec3 m_Origin;
        glm::vec3 m_Direction;
    };

}
