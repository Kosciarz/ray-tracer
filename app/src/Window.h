#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>

class Window
{
public:
    Window(const std::uint16_t width, const std::uint16_t height, const char* title);

    ~Window();

    bool ShouldClose() const;

    void PollEvents() const;

    void SwapBuffers() const;

    GLFWwindow* GetWindow();

private:
    static void Resize(GLFWwindow* window, const int width, const int height);

private:
    GLFWwindow* m_Window = nullptr;
};
