#pragma once

#include <cstdint>
#include <functional>

#include "Events/Event.hpp"

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    struct WindowConfig
    {
        std::uint32_t Width;
        std::uint32_t Height;
        std::string Title;

        WindowConfig();

        WindowConfig(const std::uint32_t width, const std::uint32_t height, const std::string& title);
    };


    class Window
    {
    public:
        static Result<Scope<Window>> Create(const WindowConfig& config = WindowConfig());

        Window() = default;

        ~Window();

        void SetEventCallback(const std::function<void(Event&)>& callback);

        bool ShouldClose() const;

        void PollEvents() const;

        void SwapBuffers() const;

        GLFWwindow* GetWindow();

    private:
        Result<void> Init(const WindowConfig& config);

    private:
        GLFWwindow* m_Window = nullptr;
        std::function<void(Event&)> m_EventCallback;
    };

}