#include "RayTracerLayer.hpp"

#include "Renderer/OpenGLHeaders.hpp"
#include <imgui.h>

#include <memory>
#include <filesystem>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <execution>

#include "Core/Color.h"

#include "Utils/Timer.hpp"
#include "Utils/Random.hpp"
#include "Utils/Utils.hpp"

#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Image.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Renderer.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    void RayTracerLayer::OnAttach()
    {
#ifndef NDEBUG
        const fs::path shaderPath{SHADERS_DIR};
        const fs::path assetPath{ASSETS_DIR};
#else
#if _WIN32
        const fs::path shaderPath{"C:\\dev\\Cpp\\RayTracer\\Shaders"};
        const fs::path assetPath{"C:\\dev\\Cpp\\RayTracer\\Assets"};
#endif
#endif 

        const auto& shaderSource = ShaderSources::Load({shaderPath / "vs.vert", shaderPath / "fs.frag"});
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
    }

    void RayTracerLayer::OnDetach()
    {
        m_VertexArray.reset();
        m_Shader.reset();
        m_Image.reset();
    }

    void raytracer::RayTracerLayer::OnUpdate(float timeStep, std::uint32_t width, std::uint32_t height)
    {
        if (!m_Image || m_ViewportWidth != width || m_ViewportHeight != height)
        {
            m_ViewportWidth = width;
            m_ViewportHeight = height;
            Render();
        }

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
        ImGui::End();
    }

    void RayTracerLayer::Render()
    {
        Timer timer;

        m_Image = Image::Create(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA, nullptr, 0);
        m_ImageData = std::vector<std::uint8_t>(m_ViewportWidth * m_ViewportHeight * 4, 0);

        for (auto y = 0; y < m_ViewportHeight; y++)
        {
            for (auto x = 0; x < m_ViewportWidth; x++)
            {
                Color pixelColor{
                    static_cast<float>(x) / (m_ViewportWidth - 1), 
                    static_cast<float>(y) / (m_ViewportHeight - 1), 
                    0.0
                };

                const auto convertedColor = ScaleColor(pixelColor);

                const auto i = (m_ViewportHeight - y - 1) * m_ViewportWidth + x;
                m_ImageData[i * 4 + 0] = convertedColor.r;
                m_ImageData[i * 4 + 1] = convertedColor.g;
                m_ImageData[i * 4 + 2] = convertedColor.b;
                m_ImageData[i * 4 + 3] = 255;
            }
        }

        m_Image->Bind();
        m_Image->SetData(m_ImageData.data());

        m_LastRenderTime = timer.ElapsedMilliseconds();
    }

}