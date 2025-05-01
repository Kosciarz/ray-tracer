#include "Application.h"

#include "RayTracerGL.h"

#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <iostream>

#include "Window.h"
#include "GlfwContext.h"
#include "AssetManager.h"
#include "Result.h"
#include "Utils.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Texture.h"

namespace fs = std::filesystem;

static void FillFrameBuffer(std::vector<std::uint8_t>& framebuffer,
    const std::int32_t width, const std::int32_t height)
{
    for (auto y = 0; y < height; y++)
    {
        for (auto x = 0; x < width; x++)
        {
            auto r = static_cast<double>(x) / (width - 1);
            auto g = static_cast<double>(y) / (height - 1);
            auto b = 0.0;

            const auto i = (height - y - 1) * width + x;
            framebuffer[i * 3 + 0] = static_cast<int>(255 * r);
            framebuffer[i * 3 + 1] = static_cast<int>(255 * g);
            framebuffer[i * 3 + 2] = static_cast<int>(255 * b);
        }
    }
}

namespace raytracer {

    Result<Application> Application::Init()
    {
#pragma region setup

#ifndef NDEBUG
        const auto shadersPath = fs::path{ASSETS_DIR} / "shaders";
        const auto texturesPath = fs::path{ASSETS_DIR} / "textures";
#else
        const auto shadersPath = fs::path{""};
        const auto texturesPath = fs::path{""};
#endif  

        auto glfwContext = GlfwContext::Create();
        if (glfwContext.IsErr())
            return Result<Application>::Err(glfwContext.Error());

        auto window = Window::Create();
        if (window.IsErr())
            return Result<Application>::Err(window.Error());

        const auto& shaderSource = ShaderSources::Load({shadersPath / "vs.vert", shadersPath / "fs.frag"});
        if (shaderSource.IsErr())
            return Result<Application>::Err(shaderSource.Error());

        const auto& shader = Shader::Create(shaderSource.Value());
        if (shader.IsErr())
            return Result<Application>::Err(shader.Error());

#pragma endregion

#pragma region buffers

        const std::vector<float> vertices = {
            // Positions         // Texture Coordinates
            1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,   // top left
           -1.0f, -1.0f, 0.0f,   0.0f, 0.0f    // bottom left 
        };

        auto vertexArray = VertexArray::Create();
        vertexArray->Bind();

        auto vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));

        vertexArray->AddVertexBuffer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        vertexArray->AddVertexBuffer(vertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

#pragma endregion

        Application app;
        app.m_GlfwContext = glfwContext.ValueMove();
        app.m_Window = window.ValueMove();
        glfwSetKeyCallback(app.m_Window->GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        app.m_AssetManager.AddVertexArray("vertexArray", vertexArray);
        app.m_AssetManager.AddShader("shader", shader.Value());


        std::int32_t imageWidth, imageHeight;
        glfwGetWindowSize(app.m_Window->GetWindow(), &imageWidth, &imageHeight);

        std::vector<std::uint8_t> framebuffer(imageWidth * imageHeight * 3, 0);
        FillFrameBuffer(framebuffer, imageWidth, imageHeight);

        auto raytracerTexture = Texture::Create(GL_TEXTURE_2D, 0, framebuffer.data(), imageWidth, imageHeight);
        app.m_AssetManager.AddTexture("raytracedTexture", raytracerTexture);
        app.m_AssetManager.GetShader("shader")->Use();
        app.m_AssetManager.GetShader("shader")->SetUniformInt("raytracedTexture", 0);


        return Result<Application>::Ok(std::move(app));
    }

    void Application::Run()
    {
        while (!m_Window->ShouldClose())
        {
            Renderer::Clear();

            const auto& vertexArray = m_AssetManager.GetVertexArray("vertexArray");
            const auto& shader = m_AssetManager.GetShader("shader");
            const auto& texture = m_AssetManager.GetTexture("raytracedTexture");

            vertexArray->Bind();
            shader->Use();
            texture->Bind();

            GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

            m_Window->PollEvents();
            m_Window->SwapBuffers();
        }
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Shutdown()
    {
    }

}