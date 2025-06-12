#pragma once

#include "Layer.hpp"

#include <memory>
#include <string>

#include "Events/Event.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"

#include "Core/Color.hpp"
#include "Core/HittableList.hpp"

namespace raytracer {

    class RayTracerLayer final : public Layer
    {
    public:
        explicit RayTracerLayer(const std::string& name);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float timeStep) override;

        void OnUIRender() override;

        void OnEvent(Event& e) override;

    private:
        void Render();

        void BuildScene();

        void WriteColor(std::size_t index, const Color& color);

    private:
        std::uint32_t m_ViewportWidth, m_ViewportHeight;
        float m_LastRenderTime = 0.0;

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<Shader> m_Shader;

        std::shared_ptr<Image> m_Image;
        std::vector<std::uint8_t> m_ImageData;

        HittableList m_World;
    };

}