#pragma once

#include <memory>

#include "Window.hpp"
#include "RayTracerLayer.hpp"

#include "Events/ApplicationEvents.hpp"

namespace raytracer {

    class Application
    {
    public:
        Application();

        void Run() const;
        void OnEvent(Event& e);

    private:
        bool OnWindowClose(const WindowCloseEvent& e);
        bool OnWindowResize(const WindowResizeEvent& e);

    private:
        Window m_Window;
        std::unique_ptr<RayTracerLayer> m_RayTracerLayer;

        bool m_Running = true;
    };

}
