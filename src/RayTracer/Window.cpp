#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Result.h"
#include "Utils.h"

#include <iostream>
#include <cstdint>
#include <memory>


WindowConfig::WindowConfig()
    : width{1280}, height{720}, title{"RayTracer"}
{
}

WindowConfig::WindowConfig(const std::uint16_t width, const std::uint16_t height, std::string title)
    : width{width}, height{height}, title{title}
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

    m_Window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
    if (!m_Window)
        return Result<void>::Err("Failed to create GLFW window");

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL(glfwGetProcAddress))
        return Result<void>::Err("Failed to initialize GLAD");

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height) {
        GL_CHECK(glViewport(0, 0, width, height));
    });

    return Result<void>::Ok();
}

Window::Window(GLFWwindow* window)
    : m_Window{window}
{
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