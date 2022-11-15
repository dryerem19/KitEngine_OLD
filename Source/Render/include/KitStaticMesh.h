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

        // Дочерние меши
        std::vector<KitStaticMesh> mChildren;

        // Материал меша
        KitMaterial mMaterial;

        // Имя меша
        std::string mName;

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
        @param filepath Путь к модели на диске для импорта 
        */
        KitStaticMesh(const std::string& filepath);

    private:

        /*
        @brief Метод инициализация меша 
        @param vertices Данные вершин
        @param indices Данные индексов
        */
        void Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>&  indices);

        /*
        @brief Рекурсивная обработка нод сцены assimp'а 
        @param pNode Указатель на ноду
        @param pScene Указатель на сцену
        @param filepath Путь к файлу модели
        */
        void ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, const std::string& filepath);

        /*
        @brief Обработка меша assimp'а
        @param pMesh Указатель на меш assimp'а
        @param pScene Указатель на сцену
        @param filepath Путь к файлу модели
        @return Экземпляр класса KitStaticMesh
        */
        KitStaticMesh ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene, const std::string& filepath);

        /*
        @brief Обработка материала assimp'а
        @param pMaterial Указатель на материал assimp'а
        @param directory Директория с моделью
        @return Экземпляр класса KitMaterial
        */
        KitMaterial ProcessAssimpMaterial(const aiMaterial* pMaterial, const std::string& directory);

        /*
        @brief Загрузка текстур
        @param pMaterial Указатель на материал assimp'а
        @param type Тип текстур, которые нужно загрузить
        @param directory Директория с моделью
        @return Список текстур std::vector<KitTexture>
        */
        std::vector<KitTexture> LoadMaterialTextures(const aiMaterial* pMaterial, aiTextureType type, 
            const std::string& directory);
    };
}