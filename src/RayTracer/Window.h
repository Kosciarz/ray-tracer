#pragma once

#include <cstdint>
#include <memory>

#include "RayTracerGL.h"

#include "Utils/Result.h"

namespace raytracer {

    struct WindowConfig
    {
        std::uint32_t width;
        std::uint32_t height;
        std::string title;

        WindowConfig();

        WindowConfig(const std::uint32_t width, const std::uint32_t height, std::string title);
    };

    class Window
    {
    public:
        using WindowPtr = std::unique_ptr<Window>;

    public:
        static Result<WindowPtr> Create(const WindowConfig& config = WindowConfig());

        Window() = default;

        explicit Window(GLFWwindow* window);

        ~Window();

        bool ShouldClose() const;

        void PollEvents() const;

        void SwapBuffers() const;

        void SetUserPointer(void* userPtr) const;

        void* GetUserPointer();

        template <typename T>
        T* GetUserPointerAs() const;

        GLFWwindow* GetWindowHandle();

    private:
        Result<void> Init(const WindowConfig& config);

    private:
        GLFWwindow* m_WindowHandle;
        void* m_UserPointer;
    };

}