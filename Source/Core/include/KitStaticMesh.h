#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitMaterial.h"
#include "KitVertex.h"

namespace Render
{
    class KitStaticMesh
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;
        
        // Материал сетки
        KitMaterial mMaterial;

        KitStaticMesh(const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);

        /*
        @brief Метод инициализация сетки 
        @param vertices Список вершин сетки
        @param indices Список индексов сетки
        */
        void Init(const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);

        void Draw();
    };
}