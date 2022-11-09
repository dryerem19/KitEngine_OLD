//
// Created by dryerem19 on 10/28/22.
//

#ifndef LEVELEDITOR_APPLICATION_H
#define LEVELEDITOR_APPLICATION_H

#include "Core/Window.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"

namespace KitEngine::Core
{
    // Основное приложение.
    // Пример использования:
    //  WindowProps props;
    //  props.Height = 600;
    //  prop.Width   = 800;
    //
    //  auto& app = Application::Instance();
    //  app.Initialize(props);
    //  app.Start();
    class Application
    {
    private:
        // Окно
        std::unique_ptr<Window> mWindow;
        // Контейнер слоёв
        LayerStack mLayerStack;
        // Указатель на слой ImGui
        ImGuiLayer* m_pImguiLayer;
        // Кол-во секунд прошедших с момента инициализации GLFW на предедущем кадре
        double mPreviousTime;
        // Флаг, запущено ли приложение
        bool mIsRunning;

    public:
        // Конструтор копирования удалён, так как это синглтон
        Application(const Application&) = delete;
        // Конструтор присваивания удалён, так как это синглтон
        Application& operator=(Application&) = delete;

        // Возвращает экземпляр класса
        static Application& Instance();

        // Инициализирует приложение
        //
        // Параметр WindowProps используется для информации о окне, которое будет создано.
        void Initialize(const KitEngine::WindowProps& props);

        // Поместить слой в контейнер слоёв
        inline void PushLayer(BaseLayer* pLayer) { mLayerStack.Push(pLayer); }

        // Удалить слой из контейнера слоёв
        inline void PopLayer(BaseLayer* pLayer) { mLayerStack.Pop(pLayer); }

        // Возвращает окно
        [[nodiscard]] inline auto& GetWindow() { return mWindow; }

        // Запускает приложение
        void Start();

        // Закрывает приложение
        void Close();

    private:
        // Закрытый конструтор, так как это синглтон
        Application();
        // Закрытый деструтор по умолчанию, так как это синглтон
        ~Application() = default;
    };
}

#endif //LEVELEDITOR_APPLICATION_H
