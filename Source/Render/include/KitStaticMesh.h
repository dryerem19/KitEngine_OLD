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
                      const std::vector<uint32_t>&  indices)
            : mVertexBuffer(vertices.data(), vertices.size()),
              mIndexBuffer(indices.data(), indices.size())
            {
                VertexBufferLayout bufferLayout;
                bufferLayout.AddFloatElement(3);
                bufferLayout.AddFloatElement(2);
                bufferLayout.AddFloatElement(3);

                mVertexArray.AddBuffer(mVertexBuffer, bufferLayout);
            }
    };
}