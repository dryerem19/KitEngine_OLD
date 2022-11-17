#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitMaterial.h"
#include "KitVertex.h"
#include "KitObject.h"
#include "KitScene.h"

namespace Render
{
    class KitStaticMesh
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;

        std::string mName;
        std::vector<KitObject> mChildren; 
        KitScene* m_pScene;
        
        // Материал меша
        KitMaterial mMaterial;

        /*
        Конструктор по умолчанию
        */
        KitStaticMesh() = default;

        /*
        @param vertices Данные вершин
        @param indices Данные индексов
        */
        KitStaticMesh(KitScene* pScene, const std::vector<KitVertex>& vertices,
                      const std::vector<uint32_t>&  indices);

        /*
        @param vertices Данные вершин
        @param indices Данные индексов
        @param material Материал
        */
        KitStaticMesh(KitScene* pScene, const std::vector<KitVertex>& vertices,
                      const std::vector<uint32_t>&  indices, const KitMaterial& material);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(KitScene* pScene, const std::vector<KitVertex>& vertices, 
                const std::vector<uint32_t>&  indices);
    };
}