#pragma once

#include "Layer.hpp"

#include <memory>
#include <string>

#include "Events/Event.hpp"

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
        RayTracerLayer(const std::string& name);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float timeStep) override;

        void OnUIRender() override;

        void OnEvent(Event& event) override;

    private:
        void Render();

        void BuildScene();

        void UpdateBuffer(const std::size_t i, const Color& color);

    private:
        std::uint32_t m_ViewportWidth, m_ViewportHeight;
        float m_LastRenderTime = 0.0;

        Ref<VertexArray> m_VertexArray;
        Ref<Shader> m_Shader;

        Ref<Image> m_Image;
        std::vector<std::uint8_t> m_ImageData;

        HittableList m_World;
    };

}