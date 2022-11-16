#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitMaterial.h"
#include "KitTransform.h"
#include "KitVertex.h"

namespace Render
{
    class KitStaticMesh
    {
    public:
        VertexArray  mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer  mIndexBuffer;
        KitTransform mTransform;

        // Дочерние меши
        std::vector<std::shared_ptr<KitStaticMesh>> mChildren;

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

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>&  indices);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(const std::string& filepath);

        std::vector<std::shared_ptr<Render::KitStaticMesh>>::iterator begin() { return mChildren.begin(); }
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::iterator end() { return mChildren.end(); }
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::const_iterator cbegin() { return mChildren.cbegin(); }
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::const_iterator cend() { return mChildren.cend(); }


    private:

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
        std::shared_ptr<KitStaticMesh> ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene, const std::string& filepath);

        /*
        @brief Обработка материала assimp'а
        @param pMaterial Указатель на материал assimp'а
        @param directory Директория с моделью
        @return Экземпляр класса KitMaterial
        */
        void ProcessAssimpMaterial(const aiMaterial* pMaterial, const std::string& directory, KitMaterial& kitMaterial);

        /*
        @brief Загрузка текстур
        @param pMaterial Указатель на материал assimp'а
        @param type Тип текстур, которые нужно загрузить
        @param directory Директория с моделью
        @return Список текстур std::vector<KitTexture>
        */
        std::vector<std::shared_ptr<KitTexture>> LoadMaterialTextures(const aiMaterial* pMaterial, aiTextureType type, 
            const std::string& directory);
    };
}