#pragma once

#include <cstdint>

class IndexBuffer
{
public:
    IndexBuffer(const void* data, std::int32_t size);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

private:
    std::uint32_t m_BufferID;
};
