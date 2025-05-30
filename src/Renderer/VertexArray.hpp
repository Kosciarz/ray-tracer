#pragma once

#include <memory>
#include <vector>

#include "OpenGLHeaders.hpp"

#include "Buffer.hpp"

#include "Utils/RayTracerUtils.hpp"

namespace raytracer {

    class VertexArray
    {
    public:
        static std::shared_ptr<VertexArray> Create();

        VertexArray();

        ~VertexArray();

        void Bind() const;

        void Unbind() const;

        void AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

        [[nodiscard]] std::shared_ptr<IndexBuffer> GetIndexBuffer() const;

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> buffer, GLuint index, GLint size, GLenum type,
            GLboolean normalized, GLsizei stride, const void* offset);

    private:
        GLuint m_VAO;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    };

}