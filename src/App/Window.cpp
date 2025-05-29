#include "Window.hpp"

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    WindowConfig::WindowConfig(const std::string& title, const std::uint32_t width, const std::uint32_t height)
        : Title{title}, Width{width}, Height{height}
    {
    }

    Window::Window(const WindowConfig& config)
        : m_Window{nullptr}, m_Title{config.Title}, m_Width{config.Width}, m_Height{config.Height}
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        s_WindowCount--;

        if (s_WindowCount == 0)
        {
            glfwTerminate();
        }
    }

    Result<Scope<Window>> Window::Create(const WindowConfig& config)
    {
        auto window = MakeScope<Window>(config);
        if (auto initResult = window->Init(); !initResult)
        {
            return Result<Scope<Window>>::Err(initResult.Error());
        }
        return Result<Scope<Window>>::Ok(std::move(window));
    }

    Result<void> Window::Init()
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
                return Result<void>::Err("Failed to initialize GLFW");
            }
        }

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        s_WindowCount++;
        if (!m_Window)
        {
            return Result<void>::Err("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGL(glfwGetProcAddress))
        {
            return Result<void>::Err("Failed to initialize GLAD");
        }

        glfwSetWindowUserPointer(m_Window, this);

        glfwSetFramebufferSizeCallback(m_Window,
            [](GLFWwindow* window, const int width, const int height)
            {
                auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                win->m_Width = width;
                win->m_Height = height;

                WindowResizeEvent event{static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)};
                win->m_EventCallback(event);
            });

        glfwSetWindowCloseCallback(m_Window,
            [](GLFWwindow* window)
            {
                const auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                win->m_EventCallback(event);
            });

        glfwSetKeyCallback(m_Window,
            [](GLFWwindow* window, const int key, int scancode, const int action, int mods)
            {
                if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                {
                    const auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
                    WindowCloseEvent event;
                    win->m_EventCallback(event);
                }
            });

        return Result<void>::Ok();
    }

    void Window::SetEventCallback(const std::function<void(Event&)>& callback)
    {
        m_EventCallback = callback;
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_Window);
    }

    GLFWwindow* Window::GetWindow() const
    {
        return m_Window;
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