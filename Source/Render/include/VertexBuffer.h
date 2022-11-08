//
// Created by dryerem19 on 21.10.22.
//

#pragma once

namespace Render
{
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
        VertexBuffer(const void* src, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}
