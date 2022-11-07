//
// Created by dryerem19 on 21.10.22.
//

#pragma once
#include "core.h"

namespace KitEngine::Graphics
{
    class VertexBuffer
    {
    private:
        unsigned int mVertexBufferId;
    public:
        VertexBuffer(const void* src, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    };
}
