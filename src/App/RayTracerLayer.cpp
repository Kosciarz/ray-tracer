#include "RayTracerLayer.hpp"

#include "Renderer/OpenGLHeaders.hpp"
#include <glm/vec3.hpp>
#include "spdlog/spdlog.h"

#include <memory>
#include <cstdint>
#include <vector>

#include "Core/Camera.hpp"
#include "Core/Sphere.hpp"

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"

#include "Utils/Timer.hpp"
#include "Utils/GLUtils.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    RayTracerLayer::RayTracerLayer(const std::uint32_t imageWidth)
        : m_ImageWidth{imageWidth}
    {
        Init();
    }

    void RayTracerLayer::Init()
    {
#ifndef NDEBUG
        const fs::path shadersPath{SHADERS_DIR};
        m_Shader = Shader::Create({shadersPath / "vs.vert", shadersPath / "fs.frag"});
#endif

        const std::vector<float> vertices = {
            1.0f,  1.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f,   1.0f, 0.0f,   // bottom right
           -1.0f,  1.0f,   0.0f, 1.0f,   // top left
           -1.0f, -1.0f,   0.0f, 0.0f    // bottom left
        };

        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();
        
        const auto vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
        m_VertexArray->AddVertexBuffer(vertexBuffer, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
        m_VertexArray->AddVertexBuffer(vertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        m_World.Add(std::make_unique<Sphere>(glm::vec3{0, 0, -1}, 0.5));
        m_World.Add(std::make_unique<Sphere>(glm::vec3{0, -100.5, -1}, 100));
    }

    void RayTracerLayer::Update()
    {
        if (!m_Image || m_ImageWidth != m_Image->Width())
            Render();

        m_VertexArray->Bind();
        m_Shader->Use();
        m_Image->Bind();

        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    }

    void RayTracerLayer::HandleEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(
            [this](const WindowResizeEvent& e)
            {
                m_ImageWidth = e.GetWidth();
                return false;
            });
    }

    void RayTracerLayer::Render()
    {
        const Timer timer;

        m_Camera.SetAspectRatio(16.0 / 9.0);
        m_Camera.SetImageWidth(m_ImageWidth);

        const auto imageData = m_Camera.Render(m_World);
        m_Image = Image::Create(m_Camera.ImageWidth(), m_Camera.ImageHeight(), ImageFormat::RGBA, imageData.data(), 0);

        spdlog::info("Render time: {:.2f}ms", timer.ElapsedMilliseconds());
    }

}
