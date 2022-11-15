//
// Created by dryerem19 on 08.11.22.
//

#ifndef KITENGINE_RENDERER_H
#define KITENGINE_RENDERER_H
#include "../pch/RenderPch.h"

#include "Shader.h"
#include "KitVertex.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "FrameBuffer.h"
#include "KitStaticMesh.h"

namespace Render
{
    class Renderer
    {
    private:
    public:
        static void Initialize()
        {
            glEnable(GL_DEPTH_TEST);
        }

        static void DrawIndexed(uint32_t count, uint32_t baseIndex, uint32_t baseVertex)
        {
            glDrawElementsBaseVertex(
                    GL_TRIANGLES,
                    count,
                    GL_UNSIGNED_INT,
                    reinterpret_cast<const void*>(sizeof(uint32_t) * baseIndex),
                    baseVertex);
        }

        static void Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    };
}

#endif //KITENGINE_RENDERER_H
