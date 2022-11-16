#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitMaterial.h"
#include "KitTransform.h"
#include "KitVertex.h"
#include "KitObject.h"

namespace Render
{
    class KitStaticMesh : public KitObject
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;

        std::vector<std::shared_ptr<KitStaticMesh>> mChildren; 
        
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
        KitStaticMesh(const std::vector<KitVertex>& vertices,
                      const std::vector<uint32_t>&  indices);

        /*
        @param vertices Данные вершин
        @param indices Данные индексов
        @param material Материал
        */
        KitStaticMesh(const std::vector<KitVertex>& vertices,
                      const std::vector<uint32_t>&  indices, const KitMaterial& material);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>&  indices);
    };
}