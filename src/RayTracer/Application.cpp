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
#include "Layer.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Image.h"

namespace fs = std::filesystem;


namespace raytracer {

    Application Application::Create()
    {
        Application app;
        auto initResult = app.Init();
        if (!initResult)
            throw std::runtime_error{initResult.Error()};

        return app;
    }

    Result<void> Application::Init()
    {
        auto glfwContext = GlfwContext::Create();
        if (glfwContext.IsErr())
            return Result<void>::Err(glfwContext.Error());

        auto window = Window::Create();
        if (window.IsErr())
            return Result<void>::Err(window.Error());

        m_GlfwContext = glfwContext.ValueMove();
        m_Window = window.ValueMove();
        glfwSetKeyCallback(m_Window->GetWindowHandle(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        return Result<void>::Ok();
    }

    void Application::Run()
    {
        m_Running = true;

        while (!m_Window->ShouldClose() && m_Running)
        {
            m_Window->PollEvents();

            std::int32_t viewportWidth, viewportHeight;
            glfwGetWindowSize(m_Window->GetWindowHandle(), &viewportWidth, &viewportHeight);

            for (const auto& layer : m_LayerStack)
                layer->OnUpdate(m_TimeStep, viewportWidth, viewportHeight);


            float time = GetTime();
            m_FrameTime = time - m_LastFrameTime;
            m_TimeStep = std::min(time, 0.0333f);
            m_LastFrameTime = time;

            m_Window->SwapBuffers();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::PushLayer(const std::shared_ptr<Layer>& layer)
    {
        m_LayerStack.emplace_back(layer);
        layer->OnAttach();
    }

    

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Shutdown()
    {
    }

}