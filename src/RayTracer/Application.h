#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Result.h"
#include "Window.h"
#include "Renderer.h"
#include "GlfwContext.h"

#include <memory>


class Application
{
public:
    Application();

    ~Application();

    static Result<Application> Init();
 
    void Run();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    Application(Application&&) = default;
    Application& operator=(Application&&) = default;

private:
    void Shutdown();

    bool m_Running;
    std::unique_ptr<GlfwContext> m_GlfwContext;
    std::unique_ptr<Window> m_Window;
    Renderer m_Renderer;
};