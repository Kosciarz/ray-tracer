#include "Application.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include <filesystem>
#include <memory>
#include <iostream>

#include "Window.hpp"
#include "LayerStack.hpp"
#include "RayTracerLayer.hpp"

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Utils/GLUtils.hpp"
#include "Utils/Result.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    Application Application::Create()
    {
        Application app{};

        auto window = Window::Create();
        if (!window)
            throw std::runtime_error{window.Error()};

        app.m_Window = std::move(window.Value());
        app.m_Window->SetEventCallback(
            [&app](Event& event)
            {
                app.OnEvent(event);
            });

        app.PushLayer(std::make_unique<RayTracerLayer>("RayTracerLayer"));
        app.PushOverlay(std::make_unique<ImGuiLayer>(app.m_Window->GetWindow()));

        return app;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            const float time = glfwGetTime();
            const float timeStep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (const auto& layer : m_LayerStack)
            {
                layer->OnUpdate(timeStep);
            }

            ImGuiLayer::Begin();
            for (const auto& layer : m_LayerStack)
            {
                layer->OnUIRender();
            }
            ImGuiLayer::End();

            m_Window->PollEvents();
            m_Window->SwapBuffers();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
            [this](const WindowCloseEvent& e)
            {
                return OnWindowClose(e);
            });

        dispatcher.Dispatch<WindowResizeEvent>(
            [this](const WindowResizeEvent& e)
            {
                return OnWindowResize(e);
            });

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(const WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(const WindowResizeEvent& e)
    {
        GL_CHECK(glViewport(0, 0, e.GetWidth(), e.GetHeight()));
        return false;
    }

}