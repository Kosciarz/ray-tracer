#pragma once

#include <memory>

#include "Window.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"

#include "Events/ApplicationEvents.hpp"

namespace raytracer {

    class Application
    {
    public:
        Application();
        ~Application() = default;

        void Run();

        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> layer);

        void OnEvent(Event& e);

    private:
        bool OnWindowClose(const WindowCloseEvent& e);
        bool OnWindowResize(const WindowResizeEvent& e);

    private:
        Window m_Window;
        LayerStack m_LayerStack;

        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
    };

}