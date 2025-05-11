#pragma once

#include <GLFW/glfw3.h>

namespace raytracer::time {

    inline float GetTime()
    {
        return static_cast<float>(glfwGetTime());
    }

}