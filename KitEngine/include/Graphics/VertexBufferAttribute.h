//
// Created by dryerem19 on 10/24/22.
//

#pragma once
#include "Renderer.h"
#include "GLTypeSize.h"

namespace KitEngine::Graphics
{
    struct VertexBufferAttribute
    {
        GLsizei   Count;
        GLsizei   Type;
        GLboolean Normalized;

        static unsigned int GetSizeOfType(unsigned int type) {
            switch (type) {
                case GL_FLOAT:
                    return GLTypeSize::Float;
                default:
                    break;
            }

            // TODO: Сделать ассерт
            return 0;
        }
    };
}