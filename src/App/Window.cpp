#include "Window.hpp"

#include <iostream>
#include <cstdint>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/Utils.hpp"

namespace raytracer {

    WindowConfig::WindowConfig()
        : width{1280}, height{720}, title{"RayTracer"}
    {
    }

    WindowConfig::WindowConfig(const std::uint32_t m_Width, const std::uint32_t height, const std::string& title)
        : width{m_Width}, height{height}, title{title}
    {
    }


    Result<Scope<Window>> Window::Create(const WindowConfig& config)
    {
        auto window = MakeScope<Window>();
        auto initResult = window->Init(config);
        if (!initResult)
            return Result<Scope<Window>>::Err(initResult.Error());
        return Result<Scope<Window>>::Ok(std::move(window));
    }

    Result<void> Window::Init(const WindowConfig& config)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

        m_Window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
        if (!m_Window)
            return Result<void>::Err("Failed to create GLFW window");

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGL(glfwGetProcAddress))
            return Result<void>::Err("Failed to initialize GLAD");

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, const int m_Width, const int height)
        {
            GL_CHECK(glViewport(0, 0, m_Width, height));
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        return Result<void>::Ok();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
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

    GLFWwindow* Window::GetWindow()
    {
        return m_Window;
    }

}