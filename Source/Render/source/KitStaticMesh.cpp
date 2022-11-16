#include "RenderPch.h"
#include "KitStaticMesh.h"

Render::KitStaticMesh::KitStaticMesh(const std::vector<KitVertex>& vertices,
                                     const std::vector<uint32_t>&  indices)
{
    // Инициализация меша
    this->Init(vertices, indices);
}

Render::KitStaticMesh::KitStaticMesh(const std::vector<KitVertex>& vertices,
                                     const std::vector<uint32_t>&  indices, 
                                     const KitMaterial& material)
                                     : mMaterial(material)
{
    // Инициализация меша
    this->Init(vertices, indices);
}

void Render::KitStaticMesh::Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>&  indices)
{
    // Инициализация буфера вершин
    mVertexBuffer.Init(vertices.data(), vertices.size() * sizeof(vertices[0]));

    // Инициализация слоя буфера
    VertexBufferLayout bufferLayout;
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(2);

    // Добавляем буфер в буфер вершин
    mVertexArray.AddBuffer(mVertexBuffer, bufferLayout);

    // Инициализация буфера индексов
    mIndexBuffer.Init(indices.data(), indices.size());
}
