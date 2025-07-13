#include "Application.hpp"

#include <memory>

#include "Window.hpp"
#include "RayTracerLayer.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Utils/GLUtils.hpp"

namespace fs = std::filesystem;

namespace raytracer {

    Application::Application()
        : m_RayTracerLayer{std::make_unique<RayTracerLayer>(m_Window.GetWidth())}
    {
        m_Window.SetEventCallback(
            [this](Event& event)
            {
                OnEvent(event);
            });
    }

    void Application::Run() const
    {
        while (m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            m_RayTracerLayer->Update();

            m_Window.PollEvents();
            m_Window.SwapBuffers();
        }
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

        m_RayTracerLayer->HandleEvent(e);
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
