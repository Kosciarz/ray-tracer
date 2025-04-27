#include <GLFW/glfw3.h>

#include "GlfwContext.h"
#include "Result.h"

#include <memory>

Result<GlfwContext::GlfwContextPtr> GlfwContext::Create()
{
    if (!glfwInit())
        return Result<GlfwContextPtr>::Err("Failed to initialize GLFW");

    auto context = std::make_unique<GlfwContext>();
    return Result<GlfwContextPtr>::Ok(std::move(context));
}

GlfwContext::~GlfwContext()
{
    glfwTerminate();
}