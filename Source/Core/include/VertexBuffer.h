//
// Created by dryerem19 on 21.10.22.
//

#pragma once

struct VertexBufferAttribute
{
    GLsizei      Count;
    GLsizei      Type;
    GLboolean    Normalized;
    GLTypeSize   TypeSize;
};

class VertexBuffer
{
private:
    uint32_t mVertexBufferId;
public:
    VertexBuffer(const void* src, const uint32_t size);
    VertexBuffer() = default;
    ~VertexBuffer();

    void Init(const void* src, const uint32_t size);
    void Bind() const;
    void Unbind() const;
};
