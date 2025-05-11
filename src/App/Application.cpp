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
#include "LayerStack.hpp"
#include "RayTracerLayer.hpp"

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Utils/RayTracerUtils.hpp"
#include "Utils/GLUtils.hpp"
#include "Utils/Result.hpp"
#include "Utils/Timer.hpp"
#include "Utils/Time.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    Application::Application()
        : m_Running{true}, m_LastFrameTime{0.0f}
    {
    }
    
    Application::~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

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
        auto window = Window::Create();
        if (!window)
            return Result<void>::Err(window.Error());

        m_Window = window.ValueMove();
        m_Window->SetEventCallback(
            [this](Event& event)
            {
                OnEvent(event);
            });

        SetupImGui();
        PushLayer(MakeScope<RayTracerLayer>("RayTracerLayer"));

        return Result<void>::Ok();
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = time::GetTime();
            float timeStep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            {
                for (const auto& layer : m_LayerStack)
                    layer->OnUpdate(timeStep);
            }


            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                for (const auto& layer : m_LayerStack)
                    layer->OnUIRender();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            m_Window->PollEvents();
            m_Window->SwapBuffers();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::PushLayer(Scope<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(Scope<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
            [this](WindowCloseEvent& e)
            {
                return OnWindowClose(e);
            });

        dispatcher.Dispatch<WindowResizeEvent>(
            [this](WindowResizeEvent& e)
            {
                return OnWindowResize(e);
            });

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        GL_CHECK(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
        return false;
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

}