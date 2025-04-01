#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>

class Window
{
public:
    Window(const std::uint16_t width, const std::uint16_t height, const char* title);

    ~Window();

    inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

    inline void PollEvents() const { glfwPollEvents(); }

    inline void SwapBuffers() const { glfwSwapBuffers(m_Window); }

    inline GLFWwindow* GetWindow() { return m_Window; }

private:
    static void Resize(GLFWwindow* window, const int width, const int height);

private:
    GLFWwindow* m_Window;
};
