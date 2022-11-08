//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_LAYERSTACK_H
#define KITENGINE_LAYERSTACK_H

#include "BaseLayer.h"

namespace KitEngine::Core
{
    // Контейнер слоёв.
    // Пример:
    //  LayerStack layerStack;
    //  BaseLayer* pLayer1 = new BaseLayer();
    //  BaseLayer* pLayer2 = new BaseLayer();
    //  layerStack.Push(pLayer1);
    //  layerStack.Push(pLayer2);
    class LayerStack
    {
    private:
        // Контейнер слоёв
        std::vector<BaseLayer*> mLayers;
    public:
        // Конструктор по умолчанию
        LayerStack() = default;
        // Деструктор
        ~LayerStack();

        // Помещает новый слой в контейнер
        void Push   (BaseLayer* pLayer);

        // Удаляет слой из контейнера
        void Pop    (BaseLayer* pLayer);

        // Возвращает контейнер с слоями
        [[nodiscard]] inline const auto& GetLayers() const { return mLayers; }
    };
}

#endif //KITENGINE_LAYERSTACK_H
