#pragma once

#include <memory>

#include "Window.hpp"
#include "LayerStack.hpp"
#include "ImGuiLayer.hpp"

#include "Events/ApplicationEvents.hpp"

#include "Utils/Result.hpp"

namespace raytracer {

    class Application
    {
    public:
        Application() = default;
        ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) noexcept = default;
        Application& operator=(Application&&) noexcept = default;

        static Application Create();

        void Run();
        void Close();

        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> layer);

        void OnEvent(Event& e);

    private:
        Result<void> Init();

        bool OnWindowClose(const WindowCloseEvent& e);
        bool OnWindowResize(const WindowResizeEvent& e);

    private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;

        bool m_Running = true;
        float m_LastFrameTime = 0.0f;
    };

}