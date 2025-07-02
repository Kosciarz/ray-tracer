#include "Window.hpp"

#include <memory>
#include <string>
#include <cstdint>

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    WindowConfig::WindowConfig(std::string title, const std::uint32_t width, const std::uint32_t height)
        : Title{std::move(title)}, Width{width}, Height{height}
    {
    }


    Window::Window(const WindowConfig& config)
        : m_GlfwWindow{nullptr}, m_Title{config.Title}, m_Width{config.Width}, m_Height{config.Height}
    {
        Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_GlfwWindow);
        s_WindowCount--;

        if (s_WindowCount == 0)
            glfwTerminate();
    }

    void Window::Init()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

        if (s_WindowCount == 0)
        {
            if (!glfwInit())
            {
                throw std::runtime_error{"Failed to initialize GLFW"};
            }
        }

        m_GlfwWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        s_WindowCount++;
        if (!m_GlfwWindow)
            throw std::runtime_error{"Failed to create GLFW window"};

        glfwMakeContextCurrent(m_GlfwWindow);

        if (!gladLoadGL(glfwGetProcAddress))
            throw std::runtime_error{"Failed to initialize GLAD"};

        glfwSetWindowUserPointer(m_GlfwWindow, this);

        glfwSetFramebufferSizeCallback(m_GlfwWindow,
            [](GLFWwindow* window, const int width, const int height)
            {
                auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                win->m_Width = width;
                win->m_Height = height;

                WindowResizeEvent event{static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)};
                win->m_EventCallback(event);
            });

        glfwSetWindowCloseCallback(m_GlfwWindow,
            [](GLFWwindow* window)
            {
                const auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                win->m_EventCallback(event);
            });

        glfwSetKeyCallback(m_GlfwWindow,
            [](GLFWwindow* window, const int key, int scancode, const int action, int mods)
            {
                if (action != GLFW_PRESS)
                    return;

                if (key == GLFW_KEY_ESCAPE)
                {
                    const auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                    WindowCloseEvent event;
                    win->m_EventCallback(event);
                }
            });
    }

    void Window::SetEventCallback(const std::function<void(Event&)>& callback)
    {
        m_EventCallback = callback;
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_GlfwWindow);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_GlfwWindow);
    }

    GLFWwindow* Window::GlfwWindow() const
    {
        return m_GlfwWindow;
    }

    std::uint32_t Window::GetWidth() const
    {
        return m_Width;
    }

    std::uint32_t Window::GetHeight() const
    {
        return m_Height;
    }

}