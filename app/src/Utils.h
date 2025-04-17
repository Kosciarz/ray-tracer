#pragma once

#include <glad/gl.h>
#include <iostream>
#include <string>

// Helper function to convert OpenGL error codes to human-readable strings
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

#ifdef DEBUG
#define GL_CHECK(x) \
    x; \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error in file " << __FILE__ \
                      << " at line " << __LINE__ \
                      << " after calling " #x ": " \
                      << GetGLErrorString(error) << " (" << error << ")" \
                      << std::endl; \
        } \
    } \

#else
#define GLCALL(x) x;
#endif
