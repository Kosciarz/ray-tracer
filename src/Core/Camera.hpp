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
        Camera();

        void Render(const HittableList& world, std::vector<std::uint8_t>& imageData);

        void SetAspectRatio(double ratio);
        void SetImageWidth(std::uint32_t width);

        double AspectRatio() const;
        std::uint32_t ImageWidth() const;
        std::uint32_t ImageHeight() const;

        glm::vec3 Center() const;
        glm::vec3 Pixel00Location() const;
        glm::vec3 PixelDeltaU() const;
        glm::vec3 PixelDeltaV() const;

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
