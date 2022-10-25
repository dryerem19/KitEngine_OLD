//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/VertexBuffer.h"

namespace KitEngine::Graphics
{
    class VertexArray
    {
        unsigned int mVertexArrayId;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferTemplate) const;
        void Enable() const;
        static void Disable();
    };
}