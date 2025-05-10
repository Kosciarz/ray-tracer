#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <utility>

#include "GlfwContext.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Events/ApplicationEvents.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class Application
    {
    public:
        Application() = default;
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        static Application Create();

        void Run();

        void Close();

        void PushLayer(Scope<Layer> layer);

        template <typename T, typename... Args>
            requires std::is_base_of_v<Layer, T>
        void PushLayer(Args&&... args);

        void PushOverlay(Scope<Layer> layer);

        template <typename T, typename... Args>
            requires std::is_base_of_v<Layer, T>
        void PushOverlay(Args&&... args);

        void OnEvent(Event& e);

        bool OnWindowClose(WindowCloseEvent& e);
        
        bool OnWindowResize(WindowResizeEvent& e);

        float GetTime() const;

        GLFWwindow* GetWindow() const;

    private:
        Result<void> Init();

        void SetupImGui();

    private:
        Scope<GlfwContext> m_GlfwContext;
        Scope<Window> m_Window;
        LayerStack m_LayerStack;

        bool m_Running = false;

        float m_FrameTime = 0.0f;
        float m_TimeStep = 0.0f;
        float m_LastFrameTime = 0.0f;
    };

    template <typename T, typename... Args>
        requires std::is_base_of_v<Layer, T>
    inline void Application::PushLayer(Args&&... args)
    {
        static_assert(std::is_constructible_v<T, Args...>, "Invalid arguments for constructing the layer.");
        m_LayerStack.PushLayer(MakeScope<T>(std::forward<Args>(args)...));
    }

    template <typename T, typename... Args>
        requires std::is_base_of_v<Layer, T>
    inline void Application::PushOverlay(Args&&... args)
    {
        static_assert(std::is_constructible_v<T, Args...>, "Invalid arguments for constructing the overlay.");
        m_LayerStack.PushOverlay(std::move(MakeScope<T>(std::forward<Args>(args)...)));
    }
}