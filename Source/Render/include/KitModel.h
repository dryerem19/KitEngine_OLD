#pragma once
#include "KitStaticMesh.h"
#include "KitMaterial.h"
#include "KitVertex.h"
#include "KitObject.h"

namespace Render
{
    class KitModel : public KitObject
    {
    private:
        // @brief Список мешей модели
        std::vector<std::shared_ptr<KitStaticMesh>> mChildren;

    public:
        // @brief Конструктор по умолчанию
        KitModel() = default;

        // @brief Конструктор копирования по умолчанию
        KitModel(const KitModel&) = default;

        // @brief Деструктор по умолчанию
        ~KitModel() = default;

        /*
        @brief Конструктор импорта модели с помощью Assimp
        */
        KitModel(const std::string& filepath);

        /*
        @brief Метод инициализация меша 
        @param filepath Путь к модели на диске для импорта 
        */
        void Init(const std::string& filepath);

        /*
        @brief Итератор
        @return Итератор на первый элемент
        */
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::iterator begin() 
        { return mChildren.begin(); }

        /*
        @brief Итератор
        @return Итератор на последний элемент
        */
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::iterator end() 
        { return mChildren.end(); }

        /*
        @brief Константный итератор
        @return Итератор на последний элемент
        */
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::const_iterator cbegin() 
        { return mChildren.cbegin(); }

        /*
        @brief Константный итератор
        @return Итератор на последний элемент
        */
        std::vector<std::shared_ptr<Render::KitStaticMesh>>::const_iterator cend() 
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