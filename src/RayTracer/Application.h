#pragma once

#include <memory>
#include <vector>

#include "RayTracerGL.h"

#include "Result.h"
#include "GlfwContext.h"
#include "Window.h"
#include "Layer.h"

namespace raytracer {

    class Application
    {
    public:
        Application() = default;

        ~Application();

        static Application Create();

        Result<void> Init();

        void Run();

        void Close();

        template <typename T>
        void PushLayer()
        {
            static_assert(std::is_base_of_v<Layer, T>, "Pushed type is not subclass of Layer!");
            m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
        }

        void PushLayer(const std::shared_ptr<Layer>& layer);

        float GetTime()
        {
            return static_cast<float>(glfwGetTime());
        }

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

    private:

        void Shutdown();

    private:
        std::unique_ptr<GlfwContext> m_GlfwContext = nullptr;
        std::unique_ptr<Window> m_Window = nullptr;
        bool m_Running = false;

        float m_FrameTime = 0.0;
        float m_TimeStep = 0.0;
        float m_LastFrameTime = 0.0;

        std::vector<std::shared_ptr<Layer>> m_LayerStack;
    };

}