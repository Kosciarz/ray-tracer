#include "GlfwContext.hpp"

#include <memory>

#include "Renderer/OpenGLHeaders.hpp"

#include "Utils/Result.hpp"
#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    Result<Scope<GlfwContext>> GlfwContext::Create()
    {
        if (!glfwInit())
            return Result<Scope<GlfwContext>>::Err("Failed to initialize GLFW");

        auto context = MakeScope<GlfwContext>();
        return Result<Scope<GlfwContext>>::Ok(std::move(context));
    }

    GlfwContext::~GlfwContext()
    {
        glfwTerminate();
    }

}