#pragma once

namespace Render
{
    /* 
    Предварительная декларация класса KitObject
    во избежание циклического включения заголовков
    */
    class KitObject;

    /*
    Сцена, где располагаются объекты 
    */
    class KitScene
    {
    private:
        
        /* Реестр всех сущностей на сцене */
        entt::registry mRegistry;

        /* Объявляем класс KitObject дружественным */
        friend class KitObject; 

        KitObject mSelectedObject;

    public:
        KitScene() = default;

        /*
        Создаёт новый объект на сцене
        @return созданный объект
        */
        KitObject CreateObject();

        /*
        Возвращает список компонентов сцены 
        @param Components список компонентов, которые нужно вернуть
        @return компоненты 
        */
        template<typename... Components>
        auto View()
        {
            return mRegistry.view<Components...>();
        }

        /*
        Возвращает объект, к которому прикреплен компонент
        @param instance экземпляр компонента
        @return объект 
        */
        template<typename Component>
        auto GetObject(const Component& instance)
        {
            const entt::entity entity = entt::to_entity(mRegistry, instance);
            return KitObject(entity, this);
        }

        void SetSelectedObject(KitObject obj)
        {
            mSelectedObject = obj;
        }

        KitObject GetSelectedObject() const
        {
            return mSelectedObject;
        }

    };
}