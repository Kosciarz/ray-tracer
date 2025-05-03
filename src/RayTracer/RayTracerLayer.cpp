#include "RayTracerLayer.h"

#include "RayTracerGL.h"

#include <memory>
#include <filesystem>
#include <iostream>
#include <cstdint>

#include "Utils.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Image.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

namespace fs = std::filesystem;

namespace raytracer {

    void RayTracerLayer::OnAttach()
    {
#ifndef NDEBUG
        const auto shadersPath = fs::path{ASSETS_DIR} / "shaders";
#endif 

        const auto& shaderSource = ShaderSources::Load({shadersPath / "vs.vert", shadersPath / "fs.frag"});
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
    }

    void raytracer::RayTracerLayer::OnUpdate(float timeStep, std::uint32_t width, std::uint32_t height)
    {
        if (!m_Image || width != m_Image->GetWidth() || height != m_Image->GetHeight())
        {
            m_ImageData = std::vector<std::uint8_t>(width * height * 4, 0);
            Render(m_ImageData, width, height);
            m_Image = Image::Create(width, height, ImageFormat::RGBA, m_ImageData.data(), 0);
        }

        m_VertexArray->Bind();
        m_Shader->Use();
        m_Image->Bind();

        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    }

    void RayTracerLayer::OnUIRender()
    {
    }

    void RayTracerLayer::Render(std::vector<std::uint8_t>& buffer,
        const std::int32_t width, const std::int32_t height) const
    {
        for (auto y = 0; y < height; y++)
        {
            for (auto x = 0; x < width; x++)
            {
                auto r = static_cast<double>(x) / (width - 1);
                auto g = static_cast<double>(y) / (height - 1);
                auto b = 0.0;

                const auto i = (height - y - 1) * width + x;
                buffer[i * 4 + 0] = static_cast<std::uint8_t>(255 * r);
                buffer[i * 4 + 1] = static_cast<std::uint8_t>(255 * g);
                buffer[i * 4 + 2] = static_cast<std::uint8_t>(255 * b);
                buffer[i * 4 + 3] = 255;
            }
        }
    }

}