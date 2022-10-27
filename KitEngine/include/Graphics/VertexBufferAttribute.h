//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "GLTypeSize.h"

namespace KitEngine::Graphics
{
    struct VertexBufferAttribute
    {
        GLsizei      Count;
        GLsizei      Type;
        GLboolean    Normalized;
        GLTypeSize   TypeSize;
    };
}