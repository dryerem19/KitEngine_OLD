#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitMaterial.h"
#include "KitSceneNode.h"
#include "KitVertex.h"
#include "KitObject.h"
#include "KitScene.h"

namespace Render
{
    class KitStaticMesh : public KitSceneNode
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;

        // Дочерние сетки
        std::vector<KitStaticMesh*> mChildren;

        // Материал сетки
        KitMaterial mMaterial;

        KitStaticMesh(const KitObject& attachedObject);

        /*
        @brief Метод инициализация сетки 
        @param vertices Список вершин сетки
        @param indices Список индексов сетки
        */
        void Init(const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);
    };
}