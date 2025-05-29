#pragma once

#include "Layer.hpp"

#include <GLFW/glfw3.h>

namespace raytracer {

    class ImGuiLayer final : public Layer
    {
    public:
        explicit ImGuiLayer(GLFWwindow* window);

        void OnAttach() override;

        void OnDetach() override;

        static void Begin();
        static void End();
        
    private:
        GLFWwindow* m_Window;
    };

}