#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Utils.h"

#include <iostream>
#include <cstdint>

Window::Window(const std::uint16_t width, const std::uint16_t height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_Window)
        throw std::runtime_error{"failed to create GLFW window"};

    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, Resize);

    if (!gladLoadGL(glfwGetProcAddress))
        throw std::runtime_error{"failed to initialize GLAD"};
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
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
