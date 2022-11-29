#pragma once
#include "KitStaticMesh.h"
#include "KitMaterial.h"
#include "KitVertex.h"
#include "KitObject.h"
#include "KitScene.h"
#include "KitTag.h"

namespace Render
{
    class KitModel
    {
    private:
        KitScene* pKitScene;
    public:
        std::string mFilepath;

        // Конструктор копирования по умолчанию
        KitModel(const KitModel&) = default;

        KitModel() = default;

        /*
        Конструктор импорта модели с помощью Assimp
        */
        KitModel(KitScene* kitScene, const std::string& filepath);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(KitScene* kitScene, const std::string& filepath);

    private:

        /*
        @brief Рекурсивная обработка нод сцены assimp'а 
        @param pNode Указатель на ноду
        @param pScene Указатель на сцену
        @param filepath Путь к файлу модели
        */
        void ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, 
            KitObject rootObject);

        /*
        @brief Обработка меша assimp'а
        @param pMesh Указатель на меш assimp'а
        @param pScene Указатель на сцену
        @param filepath Путь к файлу модели
        @return Экземпляр класса KitStaticMesh
        */
        KitTransform& ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene);

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