#include "Camera.hpp"

#include <vector>
#include <cstdint>

#include <glm/vec3.hpp>

#include "HittableList.hpp"

static void WriteColor(std::vector<uint8_t>& imageData, const std::size_t index, const raytracer::Color& color)
{
    imageData[index * 4 + 0] = color.r;
    imageData[index * 4 + 1] = color.g;
    imageData[index * 4 + 2] = color.b;
    imageData[index * 4 + 3] = 255;
}

namespace raytracer {

    std::vector<std::uint8_t> Camera::Render(const HittableList& world)
    {
        Init();

        std::vector<std::uint8_t> imageData(m_ImageWidth * m_ImageHeight * 4, 0);

        for (std::uint32_t y = 0; y < m_ImageHeight; y++)
        {
            for (std::uint32_t x = 0; x < m_ImageWidth; x++)
            {
                glm::vec3 pixelCenter = m_Pixel00Location + (static_cast<float>(x) * m_PixelDeltaU) + (static_cast<
                    float>(y) * m_PixelDeltaV);

                glm::vec3 rayDirection = glm::normalize(pixelCenter - m_Center);
                Ray r{m_Center, rayDirection};

                Color pixelColor = RayColor(r, world);
                Color convertedColor = ScaleColor(pixelColor);

                const std::size_t index = (m_ImageHeight - y - 1) * m_ImageWidth + x;
                WriteColor(imageData, index, convertedColor);
            }
        }

        return imageData;
    }

    void Camera::SetAspectRatio(const double ratio)
    {
        m_AspectRatio = ratio;
    }

    void Camera::SetImageWidth(const std::uint32_t width)
    {
        m_ImageWidth = width;
    }

    double Camera::AspectRatio() const
    {
        return m_AspectRatio;
    }

    std::uint32_t Camera::ImageWidth() const
    {
        return m_ImageWidth;
    }

    std::uint32_t Camera::ImageHeight() const
    {
        return m_ImageHeight;
    }

    void Camera::Init()
    {
        m_ImageHeight = static_cast<std::uint32_t>(m_ImageWidth / m_AspectRatio);
        m_ImageHeight = (m_ImageHeight < 1) ? 1 : m_ImageHeight;

        // Camera initialization
        m_Center = glm::vec3{0, 0, 0};
        constexpr auto focalLength = 1.0;
        constexpr auto viewportHeight = 2.0;
        const auto viewportWidth = viewportHeight * (static_cast<double>(m_ImageWidth) / m_ImageHeight);

        // Vectors across the horizontal and down the vertical viewport edges (from top-left corner)
        const glm::vec3 viewportU{viewportWidth, 0, 0};
        constexpr glm::vec3 viewportV{0, -viewportHeight, 0};

        // Horizontal and vertical delta vectors from pixel-to-pixel
        m_PixelDeltaU = viewportU / static_cast<float>(m_ImageWidth);
        m_PixelDeltaV = viewportV / static_cast<float>(m_ImageHeight);

        // Calculate the top left corner of the viewport
        glm::vec3 const viewportUpperLeft = m_Center - glm::vec3{0, 0, focalLength} - viewportU / static_cast<float>(
            2.0) - viewportV / static_cast<float>(2.0);

        // Calculate the P(0,0) pixel
        m_Pixel00Location = viewportUpperLeft + (m_PixelDeltaU + m_PixelDeltaV) / static_cast<float>(2.0);
    }

}
