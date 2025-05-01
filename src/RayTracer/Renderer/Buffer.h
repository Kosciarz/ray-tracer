#pragma once

#include <cstddef>
#include <memory>

#include "RayTracerGL.h"

namespace raytracer {

    class VertexBuffer
    {
    public:
        static std::shared_ptr<VertexBuffer> Create(const void* data, const std::size_t size);

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
        static std::shared_ptr<IndexBuffer> Create(const std::size_t size, 
            const void* data, const GLenum usage);

        IndexBuffer() = default;

        IndexBuffer(const std::size_t size, const void* data, const GLenum usage);

        ~IndexBuffer();

        std::size_t Size() const;

        GLenum IndexType() const;

        void Bind() const;

        void Unbind() const;

    private:
        GLuint m_BufferID;
        std::size_t m_Size;
    };
}