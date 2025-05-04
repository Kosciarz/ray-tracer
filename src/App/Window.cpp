#include "Window.hpp"

#include <iostream>
#include <cstdint>
#include <memory>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/Utils.hpp"

namespace raytracer {

    WindowConfig::WindowConfig()
        : width{1280}, height{720}, title{"RayTracer"}
    {
    }

    WindowConfig::WindowConfig(const std::uint32_t m_Width, const std::uint32_t height, std::string title)
        : width{m_Width}, height{height}, title{title}
    {
    }

    Result<Window::WindowPtr> Window::Create(const WindowConfig& config)
    {
        auto window = std::make_unique<Window>();
        auto initResult = window->Init(config);
        if (initResult.IsErr())
            return Result<WindowPtr>::Err(initResult.Error());
        return Result<WindowPtr>::Ok(std::move(window));
    }

    Result<void> Window::Init(const WindowConfig& config)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

        m_WindowHandle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
        if (!m_WindowHandle)
            return Result<void>::Err("Failed to create GLFW window");

        glfwMakeContextCurrent(m_WindowHandle);

        if (!gladLoadGL(glfwGetProcAddress))
            return Result<void>::Err("Failed to initialize GLAD");

        glfwSetFramebufferSizeCallback(m_WindowHandle, [](GLFWwindow* window, const int m_Width, const int height) {
            GL_CHECK(glViewport(0, 0, m_Width, height));
        });

        glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        return Result<void>::Ok();
    }

    Window::Window(GLFWwindow* window)
        : m_WindowHandle{window}, m_UserPointer{nullptr}
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_WindowHandle);
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_WindowHandle);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_WindowHandle);
    }

    void Window::SetUserPointer(void* ptr) const
    {
        glfwSetWindowUserPointer(m_WindowHandle, ptr);
    }

    void* Window::GetUserPointer()
    {
        return glfwGetWindowUserPointer(m_WindowHandle);
    }

    template <typename T>
    T* Window::GetUserPointerAs() const
    {
        return static_cast<T*>(GetUserPointer());
    }

    GLFWwindow* Window::GetWindowHandle()
    {
        return m_WindowHandle;
    }

}