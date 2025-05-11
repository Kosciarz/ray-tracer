#pragma once

#include "Layer.hpp"

#include <GLFW/glfw3.h>

#include "Events/Event.hpp"
#include "Events/ApplicationEvents.hpp"

namespace raytracer {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer(GLFWwindow* window);
        ~ImGuiLayer() = default;

        void OnAttach() override;

        void OnDetach() override;

        void Begin();

        void End();
        
    private:
        GLFWwindow* m_Window;
    };

}