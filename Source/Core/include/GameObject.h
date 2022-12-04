/**
 * @file GameObject.h
 * @author dryerem19 (mamayma@dgmail.com)
 * @brief Базовая логика игровой сущности
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright dryerem19 (c) 2022
 * 
 */
#pragma once
#include "KitStaticMesh.h"
#include "KitMaterial.h"

/**
 * @brief Базовая игровая сущность
 */
class GameObject
{
protected:
    
    /* Имя сущности */
    std::string mName;

    /* Указатель на родительскую сущность */
    GameObject* mParent { nullptr };

    /* Дочерние сущности */
    std::vector<GameObject*> mChildren;

    /* Локальная информация о трансформации */
    glm::vec3 mTranslation   = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mRotation      = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale         = { 1.0f, 1.0f, 1.0f };
    
    /* Мировая матрица объекта */
    glm::mat4 mWorldMatrix = glm::mat4(1.0f);

    /* Грязный флаг, отвечает за то, была ли изменена сущность */
    bool mIsDirty = true;

    /* Указатель на владельца */
    GameObject* mHandle { nullptr };

    /* Меш сущности */
    Render::KitStaticMesh* mMesh { nullptr };


    /* Материал */
    Render::KitMaterial* mMaterial { nullptr };

public:
    /**
     * @brief Конструктор узла
     * 
     * @param name имя узла
     */
    GameObject(const std::string& name = "Root");

    /**
     * @brief Задать новое имя сущности
     * 
     * @param name новое имя сущности
     */
    inline void SetName(const std::string& name)
    {
        mName = name;
    }

    /**
     * @brief Получить имя сущности
     * 
     * @return имя сущности
     */
    inline std::string GetName() const
    {
        return mName;
    }

    /**
     * @brief Задать родительскую сущность
     * 
     * @param parent указатель на родительскую сущность
     */
    inline void SetParent(GameObject* parent)
    {
        mParent = parent;
    }

    /**
     * @brief Получить родительскую сущность
     * 
     * @return Указатель на родительскую сущность или nullptr, если у сущности нет родителя
     */
    inline GameObject* GetParent() const
    {
        return mParent;
    }

    /**
     * @brief Прикрепить дочернюю сущность
     * 
     * @param child указатель на дочернюю сущность
     */
    void LinkChild(GameObject* pChild);

    /**
     * @brief Прикрепить дочернюю сущность по индексу
     * 
     * @param index индекс сущности
     * @param child указатель на дочернюю сущность
     */
    void LinkChildByIndex(uint32_t index, GameObject* pChild);

    /**
     * @brief Открепить сущность от родителя, если он есть
     * 
     * @param pChild указатель на дочернюю сущность, которую нужно открепить от родителя
     */
    void UnlinkParent(GameObject* pChild);

    /**
     * @brief Открепить дочернюю сущность
     * 
     * @param pChild указатель на дочернюю сущность
     */
    void UnlinkChild(GameObject* pChild);

    /**
     * @brief Открепить сущность по её индексу
     * 
     * @param index индекс дочерней сущности
     */
    void UnlinkChildByIndex(size_t index);

    /**
     * @brief Вернуть индекс дочерней сущности
     * 
     * @param pChild указатель на дочернюю сущность
     * @return индекс дочерней сущности или -1, если сущность не найдена 
     */
    size_t GetChildIndex(GameObject* pChild);

    /**
     * @brief Получить количество дочерних сущностей
     * 
     * @return size_t 
     */
    inline size_t GetCountOfChilds() const
    {
        return mChildren.size();
    }

    /**
     * @brief Найти дочернюю сущность по её имени
     * ! Функция работает медленно, т.к для поиска приходится перебирать все сущности
     * * Рекомендуется использовать FindChildByIndex()
     * 
     * @param name имя узла
     * @return указатель на сущность или nullptr, если сущность не найдена
     */
    GameObject* FindChildByName(const std::string& name);

    /**
     * @brief Получить дочернюю сущность по её индексу
     * 
     * @param index индекс дочерней сущности
     * @return Указатель на дочернюю сущность или nullptr, если она не найдена
     */
    GameObject* GetChildByIndex(size_t index) const;


    inline bool HasChilds() const
    {
        return mChildren.size();
    }

    inline GameObject* GetSelf()
    {
        return this;
    }

    /**
     * @brief Получить вектор положения сущности
     * 
     * @return Ссылка на вектор положения
     */
    inline const glm::vec3& GetPosition() const
    {
        return mTranslation;
    }

    /**
     * @brief Получить вектор поворота сущности
     * 
     * @return Ссылка на вектор поворота
     */
    inline const glm::vec3& GetRotation() const
    {
        return mRotation;
    }

    /**
     * @brief Установить локальную позицию сущности
     * 
     * @param position вектор положения сущности
     */
    inline void SetPosition(const glm::vec3& position)
    {
        mTranslation = position;
        mIsDirty = true;
    }

    /**
     * @brief Установить локальный поворот сущности в радианах
     * 
     * @param rotation вектор поворота в радианах
     */
    inline void SetRotationInRadians(const glm::vec3& rotation)
    {
        mRotation = rotation;
        mIsDirty = true;
    }

    /**
     * @brief Установить локальный поворот сущности в градусах
     * 
     * @param rotation вектор поворота в градусах
     */
    inline void SetRotationInDegrees(const glm::vec3& rotation)
    {
        mRotation.x = glm::radians(rotation.x);
        mRotation.y = glm::radians(rotation.y);
        mRotation.z = glm::radians(rotation.z);
        mIsDirty = true;
    }

    /**
     * @brief Установить локальный мастштаб сущности
     * 
     * @param scale вектор масштаба
     */
    inline void SetScale(const glm::vec3& scale)
    {
        mScale = scale;
        mIsDirty = true;
    }

    /**
     * @brief Получить вектор масштабирования сущности
     * 
     * @return Ссылка на вектор масштабирования
     */
    inline const glm::vec3& GetScale() const
    {
        return mScale;
    }

    /**
     * @brief Получить мировую матрицу сущности
     * 
     * @return Ссылка на мировую матрицу сущности
     */
    inline glm::mat4& GetWorldMatrix()
    {
        return mWorldMatrix;
    }

    /**
     * @brief Проверить, была ли изменена сущность
     * 
     * @return true, если сущность изменена
     * @return false, если сущность не изменена
     */
    inline bool IsDirty()
    {
        return mIsDirty;
    }

    /**
     * @brief Получить локальную матрицу сущности
     * 
     * @return glm::mat4 
     */
    glm::mat4 GetLocalMatrix() const;

    /**
     * @brief Обновить мировую матрицу сущности
     * 
     */
    void UpdateWorldMatrix();

    /**
     * @brief Устанавливает владельца сущности
     * 
     * @param pHandle указатель на владельца
     */
    inline void SetHandle(GameObject* pHandle)
    {
        mHandle = pHandle;
    }

    /**
     * @brief Возвращает указатель на владельца сущности 
     * 
     * @return указатель на владельца или nullptr, если владельца нет
     */
    inline GameObject* GetHandle() const
    {
        return mHandle;
    }

    /**
     * @brief Установить меш
     * 
     * @param pMesh указатель на меш
     */
    inline void SetMesh(Render::KitStaticMesh* pMesh)
    {
        mMesh = pMesh;
    }

    /**
     * @brief Нарисовать меш, если он есть
     * 
     */
    void DrawMesh(Render::Shader* pShader, const float* view_matrix, float* proj_matrix) const;

    /**
     * @brief Установить материал на сущность
     * 
     * @param pMaterial указатель на материал
     */
    inline void SetMaterial(Render::KitMaterial* pMaterial)
    {
        assert(pMaterial);

        mMaterial = pMaterial;
    }

    /**
     * @brief Получить указатель на материал
     * 
     * @return указатель на материал
     */
    inline Render::KitMaterial* GetMaterial() const
    {
        return mMaterial;
    }
};