#pragma once

#include <memory>

#include "RayTracerGL.h"

#include "Result.h"
#include "Window.h"
#include "GlfwContext.h"
#include "AssetManager.h"

namespace raytracer {

    class Application
    {
    public:
        Application() = default;

        ~Application();

        static Result<Application> Init();

        void Run();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) = default;
        Application& operator=(Application&&) = default;

    private:
        void Shutdown();

    private:
        std::unique_ptr<GlfwContext> m_GlfwContext;
        std::unique_ptr<Window> m_Window;
        AssetManager m_AssetManager;
    };
    
}