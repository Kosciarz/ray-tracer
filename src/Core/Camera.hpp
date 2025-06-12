#pragma once

#include <cstdint>
#include <vector>

#include <glm/vec3.hpp>

#include "Color.hpp"
#include "HittableList.hpp"

namespace raytracer {

    class Camera
    {
    public:
        Camera(double aspectRatio, std::uint32_t imageWidth);

        std::vector<std::uint8_t> Render(const HittableList& world) const;

        double AspectRatio() const;
        std::uint32_t ImageWidth() const;
        std::uint32_t ImageHeight() const;

    private:
        void Init();

        static void WriteColor(std::vector<uint8_t>& imageData, std::size_t index, const Color& color);

    private:
        double m_AspectRatio;
        std::uint32_t m_ImageWidth;
        std::uint32_t m_ImageHeight;

        glm::vec3 m_Center;
        glm::vec3 m_Pixel00Location;
        glm::vec3 m_PixelDeltaU;
        glm::vec3 m_PixelDeltaV;
    };

}
