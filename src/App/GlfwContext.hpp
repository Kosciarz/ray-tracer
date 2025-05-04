#pragma once

#include <memory>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"

namespace raytracer {

    class GlfwContext
    {
    public:
        using GlfwContextPtr = std::unique_ptr<GlfwContext>;

    public:
        static Result<GlfwContextPtr> Create();

        GlfwContext() = default;

        ~GlfwContext();

        GlfwContext(const GlfwContext&) = delete;
        GlfwContext& operator=(const GlfwContext&) = delete;

        GlfwContext(GlfwContext&&) = default;
        GlfwContext& operator=(GlfwContext&&) = default;
    };

}