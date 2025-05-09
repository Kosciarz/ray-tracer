#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Renderer/OpenGLHeaders.hpp"

namespace raytracer {

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename ...Args>
    Ref<T> MakeRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename ...Args>
    Scope<T> MakeScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }


    inline const char* GetGLErrorString(GLenum error)
    {
        switch (error)
        {
        case GL_NO_ERROR: return "No error";
        case GL_INVALID_ENUM: return "Invalid enum";
        case GL_INVALID_VALUE: return "Invalid value";
        case GL_INVALID_OPERATION: return "Invalid operation";
        case GL_STACK_OVERFLOW: return "Stack overflow";
        case GL_STACK_UNDERFLOW: return "Stack underflow";
        case GL_OUT_OF_MEMORY: return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
        default: return "Unknown error";
        }
    }

}

#ifndef NDEBUG
#define GL_CHECK(x) \
    x; \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            ::std::cerr << "OpenGL error in file " << __FILE__ \
                      << " at line " << __LINE__ \
                      << " after calling " #x ": " \
                      << raytracer::GetGLErrorString(error)  \
                      << " (" << error << ")" \
                      << ::std::endl; \
        } \
    } \

#else
#define GL_CHECK(x) x;
#endif

#ifndef NDEBUG
#include <cassert>

#define RAYTRACER_ASSERT(x, msg)                         \
        do {                                            \
            if (!(x)) {                                 \
                std::cerr << "Assertion failed: "       \
                          << #x << "\nMessage: "        \
                          << msg << "\nFile: "          \
                          << __FILE__ << "\nLine: "     \
                          << __LINE__ << std::endl;     \
                assert(x);                              \
            }                                           \
        } while (0)
#else
#define RAYTRACER_ASSERT(x, msg) ((void)0)
#endif