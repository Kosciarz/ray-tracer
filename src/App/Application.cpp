#include "Application.hpp"

#include "Renderer/OpenGLHeaders.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <filesystem>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <iostream>

#include "Window.hpp"
#include "GlfwContext.hpp"
#include "Layer.hpp"
#include "RayTracerLayer.hpp"

#include "Utils/RayTracerUtils.hpp"
#include "Utils/Result.hpp"
#include "Utils/Timer.hpp"

namespace fs = std::filesystem;

namespace raytracer {
    
    Application::Application()
        : m_Running{true}, m_FrameTime{0.0f}, m_TimeStep{0.0f}, m_LastFrameTime{0.0f}
    {
    }
    
    Application::~Application()
    {
        Shutdown();
    }

    Application Application::Create()
    {
        Application app;
        auto initResult = app.Init();
        if (!initResult)
            throw std::runtime_error{initResult.Error()};

        app.PushLayer<RayTracerLayer>();
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
        glfwSetKeyCallback(m_Window->GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        SetupImGui();

        return Result<void>::Ok();
    }

    void Application::Run()
    {
        m_Running = true;

        while (!m_Window->ShouldClose() && m_Running)
        {
            m_Window->PollEvents();

            {
                std::int32_t viewportWidth, viewportHeight;
                glfwGetWindowSize(m_Window->GetWindow(), &viewportWidth, &viewportHeight);

                for (const auto& layer : m_LayerStack)
                    layer->OnUpdate(m_TimeStep, viewportWidth, viewportHeight);
            }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                for (const auto& layer : m_LayerStack)
                    layer->OnUIRender();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

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

    void Application::PushLayer(const Ref<Layer>& layer)
    {
        m_LayerStack.emplace_back(layer);
        layer->OnAttach();
    }

    float Application::GetTime() const
    {
        return static_cast<float>(glfwGetTime());
    }

    GLFWwindow* Application::GetWindow() const
    {
        return m_Window->GetWindow();
    }

    void Application::SetupImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
        ImGui_ImplOpenGL3_Init();
    }

    void Application::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}