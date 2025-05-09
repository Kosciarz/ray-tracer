#pragma once

#include <cstdint>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/Utils.hpp"

namespace raytracer {

    struct WindowConfig
    {
        std::uint32_t width;
        std::uint32_t height;
        std::string title;

        WindowConfig();

        WindowConfig(const std::uint32_t width, const std::uint32_t height, const std::string& title);
    };


    class Window
    {
    public:
        static Result<Scope<Window>> Create(const WindowConfig& config = WindowConfig());

        Window() = default;

        ~Window();

        bool ShouldClose() const;

        void PollEvents() const;

        void SwapBuffers() const;

        GLFWwindow* GetWindow();

    private:
        Result<void> Init(const WindowConfig& config);

    private:
        GLFWwindow* m_Window;
    };

}