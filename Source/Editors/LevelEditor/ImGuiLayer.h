//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_IMGUILAYER_H
#define KITENGINE_IMGUILAYER_H

#include <BaseLayer.h>
#include <Application.h>
#include "UI/KitUI.h"


namespace UI
{
    // Слой ImGui. Используется для интеграции ImGui.
    // Пример:
    //  BaseLayer* pImguiLayer = new ImGuiLayer();
    //
    //  созданный слой следует поместить в LayerStack, он самостоятельно вызывает
    //  методы OnStart() и OnFinish() при инициализации и уничтожении
    class ImGuiLayer : public Core::BaseLayer
    {
    public:
        // Конструктор по умолчанию
        ImGuiLayer();
        // Деструктор
        ~ImGuiLayer() override = default;

        // Вызывается один раз при инициализации
        void OnStart() override;

        void OnBegin() override;

        void EventHandler(const Core::Event& event);

        void OnEnd() override;

        // Вызывается один раз при уничтожении
        void OnFinish() override;

        // Начать новый ImGui кадр
        static void BeginFrame();

        // Закончить ImGui кадр
        static void EndFrame();
    };
}

#endif //KITENGINE_IMGUILAYER_H