#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Window.h"
#include "GlfwContext.h"
#include "Result.h"
#include "Utils.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"

#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>


namespace fs = std::filesystem;


Result<Application> Application::Init()
{
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

    const auto& shaderSource = ShaderSources::Load({shadersPath / "vs.glsl", shadersPath / "fs.glsl"});
    if (shaderSource.IsErr())
        return Result<Application>::Err(shaderSource.Error());

    const auto& shader = Shader::Create(shaderSource.Value());
    if (shader.IsErr())
        return Result<Application>::Err(shader.Error());

    auto texture1 = Texture::Create(GL_TEXTURE_2D, GL_TEXTURE0, texturesPath / "wooden_container.jpg");
    auto texture2 = Texture::Create(GL_TEXTURE_2D, GL_TEXTURE1, texturesPath / "awesome_face.png");

#pragma region buffers

    const std::vector<float> vertices = {
        // positions         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
    };

    const std::vector<std::uint16_t> indices = {
        0, 1, 2,
        2, 3, 0
    };

    auto vertexArray = VertexArray::Create();
    vertexArray->Bind();

    auto vertexBuffer = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
    auto indexBuffer = IndexBuffer::Create(GL_UNSIGNED_SHORT, indices.size() * sizeof(std::uint16_t), indices.data(), GL_STATIC_DRAW);

    vertexArray->AddVertexBuffer(vertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    vertexArray->EnableVertexAttribArray(0);

    vertexArray->AddVertexBuffer(vertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray->EnableVertexAttribArray(1);

    vertexArray->Unbind();

#pragma endregion

    Application app;

    app.m_Window = window.ValueMove();
    glfwSetKeyCallback(app.m_Window->GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
            glfwSetWindowShouldClose(window, true);
    });

    app.m_Renderer.AddVertexArray(vertexArray);
    app.m_Renderer.AddIndexBuffer(indexBuffer);
    app.m_Renderer.AddShader(shader.Value());
    app.m_Renderer.AddTexture("texture1", texture1);
    app.m_Renderer.AddTexture("texture2", texture2);

    app.m_Renderer.GetShader()->Use();
    app.m_Renderer.GetShader()->SetUniformInt("texture1", 0);
    app.m_Renderer.GetShader()->SetUniformInt("texture2", 1);

    app.m_GlfwContext = glfwContext.ValueMove();
    app.m_Running = true;
    return Result<Application>::Ok(std::move(app));
}

Application::Application()
    : m_Running{false}
{
}

void Application::Run()
{
    while (!m_Window->ShouldClose())
    {
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

        m_Renderer.Draw();

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