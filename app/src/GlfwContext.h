#pragma once

#include <GLFW/glfw3.h>

#include "Result.h"

#include <memory>

class GlfwContext
{
public:
    using GlfwContextPtr = std::unique_ptr<GlfwContext>;

    static Result<GlfwContextPtr> Create();

    GlfwContext() = default;

    ~GlfwContext();

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;

    GlfwContext(GlfwContext&&) = default;
    GlfwContext& operator=(GlfwContext&&) = default;
};