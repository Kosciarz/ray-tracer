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

}