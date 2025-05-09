#pragma once

#include <memory>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/Utils.hpp"

namespace raytracer {

    class GlfwContext
    {
    public:
        static Result<Scope<GlfwContext>> Create();

        GlfwContext() = default;

        ~GlfwContext();

        GlfwContext(const GlfwContext&) = delete;
        GlfwContext& operator=(const GlfwContext&) = delete;

        GlfwContext(GlfwContext&&) = default;
        GlfwContext& operator=(GlfwContext&&) = default;
    };

}