#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <utility>

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
        Application();
        ~Application();

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

        void SetupImGui();

        bool OnWindowClose(WindowCloseEvent& e);

        bool OnWindowResize(WindowResizeEvent& e);

    private:
        Scope<Window> m_Window;
        LayerStack m_LayerStack;

        bool m_Running;

        float m_FrameTime;
        float m_TimeStep;
        float m_LastFrameTime;
    };

}