#include "RenderPch.h"
#include "KitStaticMesh.h"

Render::KitStaticMesh::KitStaticMesh(const std::vector<KitVertex>& vertices,
                                     const std::vector<uint32_t>&  indices)
{
    mVertexBuffer.Init(vertices.data(), vertices.size());

    VertexBufferLayout bufferLayout;
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(2);
    bufferLayout.AddFloatElement(3);

    mVertexArray.AddBuffer(mVertexBuffer, bufferLayout);

    mIndexBuffer.Init(indices.data(), indices.size());
}