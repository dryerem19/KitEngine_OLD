//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"

namespace KitEngine::Graphics
{
    class VertexArray
    {
        unsigned int mVertexArrayId;
    public:
        VertexArray();
        VertexArray(VertexBuffer vertexBuffer, VertexBufferLayout layout);
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) const;
        void Bind() const;
        static void Unbind();
    };
}