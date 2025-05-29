#pragma once

#include <memory>

#include "Window.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"

#include "Events/ApplicationEvents.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class Application
    {
    public:
        Application();
        ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        static Application Create();

        void Run();

        void Close();

        void PushLayer(Scope<Layer> layer);

        void PushOverlay(Scope<Layer> layer);

        void OnEvent(Event& e);

    private:
        Result<void> Init();

        bool OnWindowClose(const WindowCloseEvent& e);

        bool OnWindowResize(const WindowResizeEvent& e);

    private:
        Scope<Window> m_Window;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

        bool m_Running;

        float m_LastFrameTime;
    };

}