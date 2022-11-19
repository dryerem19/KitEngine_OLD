#pragma once
#include "KitScene.h"
#include "KitTransform.h"

namespace Render
{
    /* 
    Предварительная декларация класса KitScene
    во избжание цикличного включения заголовков
    */    
    class KitScene;

    /* Объект сцены */
    class KitObject
    {
    private:

        /* Идентификатор сущности */
        entt::entity mHandle { entt::null };

        /* Указатель на сцену, которой принадлежит объект */
        KitScene* m_pScene { nullptr };

    public:
        /* Название объекта */
        std::string mName;

        KitObject() = default;
        
        /* 
        Констуктор для создания объекта в конкретной сцене
        @param handle идентификатор сущности
        @param pScene указатель на сцену, которой принадлежит объект
        */
        KitObject(entt::entity handle, KitScene* pScene)
            : mHandle(handle), m_pScene(pScene) { }

        /* Деструктор по умолчанию */
        ~KitObject() = default;       

        /*
        Добавляет компонент объекту
        @param T тип класса компонента, который следует добавить
        @param Args параметры, которые будут переданы в конструктор класса T
        @return созданный компонент
        */
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return m_pScene->mRegistry.emplace<T>(mHandle, std::forward<Args>(args)...);
        }

        /*
        Возвращает компонент объекта
        @param T тип класса компонента, который нужно получить
        @return компонент T объекта 
        */
        template<typename T>
        T& GetComponent()
        {
            return m_pScene->mRegistry.get<T>(mHandle);           
        }

        /*
        Вовзращает указатель на сцену на которой расположен объект
        @return указатель на сцену
        */
        KitScene* GetScene() const 
        {
            return m_pScene;
        }

        operator bool() const
        {
            return mHandle != entt::null;
        }        
    };
}