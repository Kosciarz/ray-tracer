#include "GlfwContext.h"

#include <memory>

#include "Renderer/OpenGLHeaders.h"

#include "Utils/Result.h"

namespace raytracer {

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

}