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

    public:
        KitScene() = default;

        /*
        Создаёт новый объект на сцене
        @return созданный объект
        */
        KitObject CreateObject();

        /*
        Возвращает список всех компонентов сцены 
        @param Components список компонентов, которые нужно вернуть
        @return компоненты 
        */
        template<typename... Components>
        auto View()
        {
            return mRegistry.view<Components...>();
        }

    };
}