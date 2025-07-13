#pragma once

#include <functional>
#include <string>
#include <cstdint>

#include "Events/Event.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    struct WindowConfig
    {
        std::string Title;
        std::uint32_t Width;
        std::uint32_t Height;

        explicit WindowConfig(std::string title = "Ray Tracer", std::uint32_t width = 1280, std::uint32_t height = 720);
    };

    class Window
    {
    public:
        explicit Window(const WindowConfig& config = WindowConfig());
        ~Window();

        void SetEventCallback(const std::function<void(Event&)>& callback);

        bool ShouldClose() const;
        void PollEvents() const;
        void SwapBuffers() const;

        GLFWwindow* GlfwWindow() const;
        [[nodiscard]] std::uint32_t GetWidth() const;
        [[nodiscard]] std::uint32_t GetHeight() const;

    private:
        void Init();

    private:
        GLFWwindow* m_GlfwWindow;
        std::string m_Title;
        std::uint32_t m_Width;
        std::uint32_t m_Height;

        std::function<void(Event&)> m_EventCallback;

    private:
        inline static std::size_t s_WindowCount = 0;
    };

}
