#pragma once

#include <GLFW/glfw3.h>

#include "Result.h"

#include <cstdint>
#include <memory>


struct WindowConfig
{
    std::uint16_t width;
    std::uint16_t height;
    std::string title;

    WindowConfig();

    WindowConfig(const std::uint16_t width, const std::uint16_t height, std::string title);
};

class Window
{
public:
    using WindowPtr = std::unique_ptr<Window>;

public:
    static Result<WindowPtr> Create(const WindowConfig& config = WindowConfig());

    Window() = default;

    explicit Window(GLFWwindow* window);

    ~Window();

    bool ShouldClose() const;

    void PollEvents() const;

    void SwapBuffers() const;

    GLFWwindow* GetWindow();

private:
    Result<void> Init(const WindowConfig& config);

private:
    GLFWwindow* m_Window;
};