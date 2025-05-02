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

        void Render(std::vector<std::uint8_t>& framebuffer,
            const std::int32_t width, const std::int32_t height) const;

    private:
        std::vector<std::uint8_t> m_ImageData;

        std::shared_ptr<raytracer::VertexArray> m_VertexArray;
        std::shared_ptr<raytracer::Shader> m_Shader;
        std::shared_ptr<raytracer::Image> m_Image;
    };

}