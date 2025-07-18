#pragma once

#include <cstdint>
#include <vector>

#include <glm/vec3.hpp>

#include "Color.hpp"
#include "HittableList.hpp"

namespace raytracer {

    using Point3 = glm::vec3;

    class Camera
    {
    public:
        Camera() = default;

        std::vector<std::uint8_t> Render(const HittableList& world);

        void SetAspectRatio(double ratio);
        void SetImageWidth(std::uint32_t width);

        double AspectRatio() const;
        std::uint32_t ImageWidth() const;
        std::uint32_t ImageHeight() const;

    private:
        void Init();

    private:
        double m_AspectRatio;
        std::uint32_t m_ImageWidth;
        std::uint32_t m_ImageHeight;

        Point3 m_Center;
        Point3 m_Pixel00Location;
        glm::vec3 m_PixelDeltaU;
        glm::vec3 m_PixelDeltaV;
    };

}
