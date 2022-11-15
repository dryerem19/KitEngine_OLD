#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitVertex.h"

namespace Render
{
    class KitStaticMesh
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;

        KitStaticMesh(const std::vector<KitVertex>& vertices,
                      const std::vector<uint32_t>&  indices);
    };
}