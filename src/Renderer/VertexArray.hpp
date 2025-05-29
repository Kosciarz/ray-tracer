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
        static Ref<VertexArray> Create();

        VertexArray();

        ~VertexArray();

        void Bind() const;

        void Unbind() const;

        void AddIndexBuffer(Ref<IndexBuffer> indexBuffer);

        [[nodiscard]] Ref<IndexBuffer> GetIndexBuffer() const;

        void AddVertexBuffer(Ref<VertexBuffer> buffer, GLuint index, GLint size, GLenum type,
            GLboolean normalized, GLsizei stride, const void* offset);

    private:
        GLuint m_VAO;
        Ref<IndexBuffer> m_IndexBuffer;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    };

}