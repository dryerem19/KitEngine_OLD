#pragma once
#include "KitStaticMesh.h"
#include "KitMaterial.h"
#include "KitVertex.h"
#include "KitObject.h"
#include "KitScene.h"

namespace Render
{
    class KitModel
    {
    public:
        // Список мешей модели
        std::vector<KitObject> mChildren;

        // Сцена, на которой расположена модель
        KitScene* m_pScene { nullptr };

        std::string mFilepath;
        std::string mName;

        // Конструктор копирования по умолчанию
        KitModel(const KitModel&) = default;

        /*
        Конструктор импорта модели с помощью Assimp
        */
        KitModel(KitScene* pScene, const std::string& filepath);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(KitScene* pScene, const std::string& filepath);

        /*
        @brief Итератор
        @return Итератор на первый элемент
        */
        std::vector<Render::KitObject>::iterator begin() 
        { return mChildren.begin(); }

        /*
        @brief Итератор
        @return Итератор на последний элемент
        */
        std::vector<Render::KitObject>::iterator end() 
        { return mChildren.end(); }

        /*
        @brief Константный итератор
        @return Итератор на последний элемент
        */
        std::vector<Render::KitObject>::const_iterator cbegin() 
        { return mChildren.cbegin(); }

        /*
        @brief Константный итератор
        @return Итератор на последний элемент
        */
        std::vector<Render::KitObject>::const_iterator cend() 
        { return mChildren.cend(); }        

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
        KitObject ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene, const std::string& filepath);

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