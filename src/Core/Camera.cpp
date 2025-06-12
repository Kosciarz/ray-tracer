#include "Camera.hpp"

#include "HittableList.hpp"

namespace raytracer {

    Camera::Camera()
        : m_AspectRatio{1.0}, m_ImageWidth{100}, m_ImageHeight{0}, m_Center{}, m_Pixel00Location{},
          m_PixelDeltaU{}, m_PixelDeltaV{}
    {
    }

    void Camera::Render(const HittableList& world, std::vector<std::uint8_t>& imageData)
    {
        Init();
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

    glm::vec3 Camera::Center() const
    {
        return m_Center;
    }

    glm::vec3 Camera::Pixel00Location() const
    {
        return m_Pixel00Location;
    }

    glm::vec3 Camera::PixelDeltaU() const
    {
        return m_PixelDeltaU;
    }

    glm::vec3 Camera::PixelDeltaV() const
    {
        return m_PixelDeltaV;
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
        glm::vec3 const viewportUpperLeft = m_Center - glm::vec3{0, 0, focalLength}
            - viewportU / static_cast<float>(2.0) - viewportV / static_cast<float>(2.0);

        // Calculate the P(0,0) pixel
        m_Pixel00Location = viewportUpperLeft + (m_PixelDeltaU + m_PixelDeltaV) / static_cast<float>(2.0);
    }

    void Camera::WriteColor(std::vector<uint8_t>& imageData, const std::size_t index, const Color& color)
    {
        imageData[index * 4] = color.r;
        imageData[index * 4 + 1] = color.g;
        imageData[index * 4 + 2] = color.b;
        imageData[index * 4 + 3] = 0;
    }

}