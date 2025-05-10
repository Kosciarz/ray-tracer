#pragma once

#include "Layer.hpp"

#include <memory>

#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Renderer.hpp"

#include "Core/Color.hpp"
#include "Core/HittableList.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class RayTracerLayer : public Layer
    {
    public:
        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float timeStep, const std::uint32_t width, const std::uint32_t height) override;

        void OnUIRender() override;

    private:
        void Render();

    private:
        std::uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        float m_LastRenderTime = 0.0;

        Ref<VertexArray> m_VertexArray;
        Ref<Shader> m_Shader;

        Ref<Image> m_Image;
        std::vector<std::uint8_t> m_ImageData;

        HittableList m_World;
    };

}