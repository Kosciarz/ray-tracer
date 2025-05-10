#pragma once

#include <memory>
#include <vector>

#include "Renderer/OpenGLHeaders.hpp"

#include "GlfwContext.hpp"
#include "Window.hpp"
#include "Layer.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

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
            requires std::is_base_of_v<Layer, T>
        {
            m_LayerStack.emplace_back(MakeRef<T>())->OnAttach();
        }

        void PushLayer(const Ref<Layer>& layer);

        float GetTime() const;

        GLFWwindow* GetWindow() const;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

    private:
        void SetupImGui();

        void Shutdown();

    private:
        Scope<GlfwContext> m_GlfwContext = nullptr;
        Scope<Window> m_Window = nullptr;
        bool m_Running = false;

        float m_FrameTime = 0.0;
        float m_TimeStep = 0.0;
        float m_LastFrameTime = 0.0;

        std::vector<Ref<Layer>> m_LayerStack;
    };

}