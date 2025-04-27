#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Result.h"
#include "Utils.h"

#include <iostream>
#include <cstdint>
#include <memory>

Result<Window::WindowPtr> Window::Create(const std::uint16_t width, const std::uint16_t height, const char * title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

    auto window = std::make_unique<Window>();
    window->m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window->m_Window)
        return Result<WindowPtr>::Err("Failed to create GLFW window");

    glfwMakeContextCurrent(window->m_Window);

    if (!gladLoadGL(glfwGetProcAddress))
        return Result<WindowPtr>::Err("Failed to initialize GLAD");
    
    glfwSetFramebufferSizeCallback(window->m_Window, Resize);

    return Result<WindowPtr>::Ok(std::move(window));
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

void Window::Resize(GLFWwindow* window, const int width, const int height)
{
    GL_CHECK(glViewport(0, 0, width, height));
}
