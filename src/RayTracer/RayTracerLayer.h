#pragma once

#include "Layer.h"

#include <memory>

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Image.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

namespace raytracer {

    class RayTracerLayer : public Layer
    {
    public:
        virtual void OnAttach() override;

        void OnDetach() override;

        virtual void OnUpdate(float timeStep, const std::uint32_t width, const std::uint32_t height) override;

        void OnUIRender() override;

        void Render();

    private:
        std::uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        float m_LastRenderTime = 0.0;

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<Shader> m_Shader;

        std::shared_ptr<Image> m_Image;
        std::vector<std::uint8_t> m_ImageData;
    };

}