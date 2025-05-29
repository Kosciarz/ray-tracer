#include "RayTracerLayer.hpp"

#include "Renderer/OpenGLHeaders.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <memory>
#include <filesystem>
#include <iostream>
#include <cstdint>
#include <vector>

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"

#include "Utils/Timer.hpp"
#include "Utils/Random.hpp"
#include "Utils/RayTracerUtils.hpp"
#include "Utils/GLUtils.hpp"

#include "Core/Color.hpp"
#include "Core/Ray.hpp"
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
        const fs::path assetPath{ASSETS_DIR};
#endif


        ShaderPaths paths{shaderPath / "vs.vert", shaderPath / "fs.frag"};
        const auto& shaderSource = ShaderSources::Load(paths);
        if (!shaderSource)
            throw std::runtime_error{shaderSource.Error()};

        const auto& shader = Shader::Create(shaderSource.Value());
        if (!shader)
            throw std::runtime_error{shader.Error()};

        m_Shader = shader.Value();

        const std::vector<float> vertices = {
            // Positions         // Texture Coordinates
            1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,   // top left
           -1.0f, -1.0f, 0.0f,   0.0f, 0.0f    // bottom left 
        };

        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();
        auto vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
        m_VertexArray->AddVertexBuffer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
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
        {
            Render();
        }
        if (ImGui::Button("Build Scene"))
        {
            BuildScene();
        }
        ImGui::End();
    }

    void RayTracerLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(
            [this](WindowResizeEvent& e)
            {
                m_ViewportWidth = e.GetWidth();
                m_ViewportHeight = e.GetHeight();

                return false;
            });
    }

    void RayTracerLayer::BuildScene()
    {
        m_World.Clear();

        m_World.Add(MakeRef<Sphere>(glm::vec3{0, 0, -1}, 0.5));
        m_World.Add(MakeRef<Sphere>(glm::vec3{0, -100.5, -1}, 100));
    }

    void RayTracerLayer::Render()
    {
        Timer timer;

        // 16/9 = imageWidth / imageHeight (ideal aspect ratio)
        float aspectRatio = 16.0 / 9.0;
        std::uint32_t imageWidth = m_ViewportWidth;
        std::uint32_t imageHeight = static_cast<std::int32_t>(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        // Camera initialization
        // Focal lenght is the distance of the camera from the virtual viewport
        // The virtual viewport is an imaginary plane that we shoot rays onto and get the color back
        // The height is set to 2 so that the bottom is -1 and and top is 1
        // and the distance of each ray from the camera center to it's pixel is not too high
        float focalLenght = 1.0;
        float viewportHeight = 2.0;
        float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);
        glm::vec3 cameraCenter{0, 0, 0};

        // Vectors across the horizontal and down the vertical viewport edges (from top-left corner)
        glm::vec3 viewportU{viewportWidth, 0, 0};
        glm::vec3 viewportV{0, -viewportHeight, 0};

        // Horizontal and vertical delta vectors from pixel-to-pixel 
        glm::vec3 pixelDeltaU = viewportU / static_cast<float>(imageWidth);
        glm::vec3 pixelDeltaV = viewportV / static_cast<float>(imageHeight);

        // Calculate the top left corner of the viewport (Q on the example)
        glm::vec3 viewportUpperLeft = cameraCenter - glm::vec3{0, 0, focalLenght}
        - viewportU / static_cast<float>(2.0) - viewportV / static_cast<float>(2.0);

        // Calulucate the P(0,0) pixel 
        glm::vec3 pixel00Location = viewportUpperLeft + (pixelDeltaU + pixelDeltaV) / static_cast<float>(2.0);


        m_Image = Image::Create(imageWidth, imageHeight, ImageFormat::RGBA, nullptr, 0);
        m_ImageData = std::vector<std::uint8_t>(imageWidth * imageHeight * 4, 0);

        for (std::uint32_t y = 0; y < imageHeight; y++)
        {
            for (std::uint32_t x = 0; x < imageWidth; x++)
            {
                glm::vec3 pixelCenter = pixel00Location
                    + (static_cast<float>(x) * pixelDeltaU) + (static_cast<float>(y) * pixelDeltaV);

                glm::vec3 rayDirection = glm::normalize(pixelCenter - cameraCenter);
                Ray r{cameraCenter, rayDirection};

                Color pixelColor = RayColor(r, m_World);
                Color convertedColor = ScaleColor(pixelColor);

                const std::size_t i = (imageHeight - y - 1) * imageWidth + x;
                UpdateBuffer(i, convertedColor);
            }
        }

        m_Image->SetData(m_ImageData.data());

        m_LastRenderTime = timer.ElapsedMilliseconds();
    }

    void RayTracerLayer::UpdateBuffer(const std::size_t i, const Color& color)
    {
        m_ImageData[i * 4 + 0] = color.r;
        m_ImageData[i * 4 + 1] = color.g;
        m_ImageData[i * 4 + 2] = color.b;
        m_ImageData[i * 4 + 3] = 255;
    }

}