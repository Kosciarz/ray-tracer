#pragma once

#include <functional>
#include <string>

#include "Events/Event.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    struct WindowConfig
    {
        std::string Title;
        std::uint32_t Width;
        std::uint32_t Height;

        explicit WindowConfig(const std::string& title = "Ray Tracer",
                              const std::uint32_t width = 1280,
                              const std::uint32_t height = 720);
    };


    class Window
    {
    public:
        explicit Window(const WindowConfig& config);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) noexcept = default;
        Window& operator=(Window&&) noexcept = default;

        static Result<Scope<Window>> Create(const WindowConfig& config = WindowConfig());

        void SetEventCallback(const std::function<void(Event&)>& callback);

        bool ShouldClose() const;

        void PollEvents() const;

        void SwapBuffers() const;

        GLFWwindow* GetWindow() const;

        std::uint32_t GetWidth() const;
        std::uint32_t GetHeight() const;

    private:
        Result<void> Init();

    private:
        GLFWwindow* m_Window;
        std::string m_Title;
        std::uint32_t m_Width;
        std::uint32_t m_Height;

        std::function<void(Event&)> m_EventCallback;
    };

}