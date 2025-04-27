#pragma once

#include <GLFW/glfw3.h>

#include "Result.h"

#include <cstdint>
#include <memory>

class Window
{
public:
    using WindowPtr = std::unique_ptr<Window>;

public:
    static Result<WindowPtr> Create(const std::uint16_t width, const std::uint16_t height, const char* title);

    Window() = default;

    explicit Window(GLFWwindow* window);

    ~Window();

    bool ShouldClose() const;

    void PollEvents() const;

    void SwapBuffers() const;

    GLFWwindow* GetWindow();

private:
    static void Resize(GLFWwindow* window, const int width, const int height);

private:
    GLFWwindow* m_Window;
};