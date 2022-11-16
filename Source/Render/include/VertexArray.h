//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Render
{
    class VertexArray
    {
        uint32_t mVertexArrayId;
    public:
        VertexArray();
        VertexArray(VertexBuffer vertexBuffer, VertexBufferLayout layout);
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const;
        void Bind() const;

        uint32_t GetId() const { return mVertexArrayId; }

        static void Unbind();
    };
}