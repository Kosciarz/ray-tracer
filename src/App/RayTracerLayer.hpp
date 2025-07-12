#pragma once

#include <memory>

#include "Core/Camera.hpp"
#include "Core/HittableList.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"

#include "Events/Event.hpp"

namespace raytracer {

    class RayTracerLayer
    {
    public:
        explicit RayTracerLayer(std::uint32_t imageWidth);

        void Update();
        void HandleEvent(Event& e);

    private:
        void Init();
        void Render();

    private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Image> m_Image;

        HittableList m_World;
        Camera m_Camera;

        std::uint32_t m_ImageWidth;
        float m_LastRenderTime = 0.0;
    };

}