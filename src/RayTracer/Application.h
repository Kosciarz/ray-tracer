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
        bool m_Running;
        std::unique_ptr<GlfwContext> m_GlfwContext;
        std::unique_ptr<Window> m_Window;
        AssetManager m_AssetManager;
        //std::shared_ptr<VertexArray> m_VertexArray;
        //std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
        //std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
    
}