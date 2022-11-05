//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_BASELAYER_H
#define KITENGINE_BASELAYER_H

#include "KitEnginePch.h"

namespace KitEngine::Core
{
    // Интерфейс базового слоя.
    // Пример:
    //  class MyLayer : public BaseLayer {
    //      public:
    //          void OnStart    ()   override;   Здесь помещаем код инициализации
    //          void OnUpdate   ()   override;   Здесь помещаем код обновления
    //          void OnRender   ()   override;   Здесь помещаем код рисования
    //          void OnUIRender ()   override;   Здесь помещаем код рисования ImGui
    //          void OnFinish   ()   override;   Здесь помещаем код освобождения ресурсов
    // }
    struct BaseLayer
    {
    public:
        // Конструктор базового класса.
        explicit BaseLayer(std::string  name = "BaseLayer");
        // Виртуальный деструктор базового класса
        virtual ~BaseLayer() = default;

        // Вызывается при инициализации слоя,
        //
        // вызывается автоматически, если был помещён в LayerStack.
        virtual void OnStart();

        // Вызывается каждый кадр.
        //
        // Следует иметь ввиду, что этот метод может быть вызван n раз, чтобы догнать разницу
        // между текущим и предедущим кадром, поэтому в данный метод слудет строго помещать код обновления,
        // но не рисования или других критических частей.
        virtual void OnUpdate();

        // Вызывается каждый кадр в момент рисования кадра, вызывается один раз за весь кадр.
        //
        // Используется для помещения в него кода рисования.
        virtual void OnRender(double dt);

        // Вызывается каждый кадр в момент рисования кадра ImGui.
        //
        // Используется для помещения в него кода рисования интерфейса
        virtual void OnUIRender();

        // Вызывается один раз при уничтожении слоя.
        //
        // Используется для помещения в него кода, который должен уничтожать ресурсы при завершении слоя
        virtual void OnFinish();

        // Возвращает имя слоя
        //
        // Имя слоя может использоваться при отладочном выводе.
        [[nodiscard]] inline const std::string& GetName() const { return mName; }

    protected:
        // Имя слоя
        std::string mName;
    };
}

#endif //KITENGINE_BASELAYER_H
