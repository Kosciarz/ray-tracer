#include "RayTracerLayer.hpp"

#include "Renderer/OpenGLHeaders.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <memory>
#include <filesystem>
#include <iostream>
#include <vector>

#include "Core/Camera.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Random.hpp"
#include "Utils/GLUtils.hpp"

#include "Core/Color.hpp"
#include "Core/Sphere.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    RayTracerLayer::RayTracerLayer(const std::string& name)
        : Layer{name}, m_ViewportWidth{1280}, m_ViewportHeight{720}
    {
    }

    void RayTracerLayer::OnAttach()
    {
#ifndef NDEBUG
        const fs::path shaderPath{SHADERS_DIR};
        ShaderPaths paths{shaderPath / "vs.vert", shaderPath / "fs.frag"};
        m_Shader = Shader::Create(paths);
#endif

        const std::vector vertices = {
            // Positions         // Texture Coords
            1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,   // top left
           -1.0f, -1.0f, 0.0f,   0.0f, 0.0f    // bottom left 
        };

        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();
        const auto vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
        m_VertexArray->AddVertexBuffer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
        m_VertexArray->AddVertexBuffer(vertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        BuildScene();
    }

    void RayTracerLayer::OnDetach()
    {
        m_VertexArray.reset();
        m_Shader.reset();
        m_Image.reset();
    }

    void RayTracerLayer::OnUpdate(float timeStep)
    {
        if (!m_Image)
            Render();

        m_VertexArray->Bind();
        m_Shader->Use();
        m_Image->Bind();

        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    }

    void RayTracerLayer::OnUIRender()
    {
        ImGui::Begin("Settings");
        ImGui::Text("Last render time: %.3fms", m_LastRenderTime);

        if (ImGui::Button("Render"))
            Render();

        if (ImGui::Button("Build Scene"))
            BuildScene();

        ImGui::End();
    }

    void RayTracerLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(
            [this](const WindowResizeEvent& e)
            {
                m_ViewportWidth = e.GetWidth();
                m_ViewportHeight = e.GetHeight();
                return false;
            });
    }

    void RayTracerLayer::BuildScene()
    {
        m_World.Clear();

        m_World.Add(std::make_unique<Sphere>(glm::vec3{0, 0, -1}, 0.5));
        m_World.Add(std::make_unique<Sphere>(glm::vec3{0, -100.5, -1}, 100));
    }

    void RayTracerLayer::Render()
    {
        Timer timer;
        Camera camera(16.0 / 9.0, m_ViewportWidth);

        auto imageData = camera.Render(m_World);
        m_Image = Image::Create(camera.ImageWidth(), camera.ImageHeight(), ImageFormat::RGBA, imageData.data(), 0);

        m_LastRenderTime = timer.ElapsedMilliseconds();
    }

}