#pragma once

#include <memory>

#include "OpenGLHeaders.hpp"

namespace raytracer {

    class VertexBuffer
    {
    public:
        VertexBuffer(const void* data, std::size_t size);
        ~VertexBuffer();

        static std::shared_ptr<VertexBuffer> Create(const void* data, std::size_t size);

        void Bind() const;
        void Unbind() const;

        void UpdateData(const void* data, std::size_t size) const;

    private:
        GLuint m_ID;
    };


    class IndexBuffer
    {
    public:
        IndexBuffer(std::size_t size, const void* data);
        ~IndexBuffer();

        static std::shared_ptr<IndexBuffer> Create(std::size_t size, const void* data);

        void Bind() const;
        void Unbind() const;

        [[nodiscard]] std::size_t Size() const;

    private:
        GLuint m_ID;
        std::size_t m_Size;
    };
}
