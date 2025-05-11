#pragma once

#include <cstddef>

#include "OpenGLHeaders.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(const void* data, const std::size_t size);

        VertexBuffer(const void* data, const std::size_t size);

        ~VertexBuffer();

        void Bind() const;

        void Unbind() const;

        void UpdateData(const void* data, const std::size_t size) const;

    private:
        GLuint m_BufferID;
    };


    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(const std::size_t size, const void* data);

        IndexBuffer(const std::size_t size, const void* data);

        ~IndexBuffer();

        void Bind() const;

        void Unbind() const;

        const std::size_t& Size() const;

    private:
        GLuint m_BufferID;
        std::size_t m_Size;
    };
}