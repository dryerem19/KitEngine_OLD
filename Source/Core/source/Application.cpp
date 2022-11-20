//
// Created by dryerem19 on 10/28/22.
//
#include "Application.h"
#include "Input.h"
#include "Logger.h"

#include <Renderer.h>

//------------------------------------------------------------------------------------
// PUBLIC SECTION
//------------------------------------------------------------------------------------

Core::Application &Core::Application::Instance() {

    static Application instance;
    return instance;

}

void Core::Application::Initialize(const WindowProps& props) {

    // Инициализация окна
    mWindow = std::make_unique<Window>(props);

    const auto& handler = std::bind(&Application::EventHandler, this, std::placeholders::_1);
    mWindow->SetEventHandlerCallback(handler);
    mWindow->Init();

    // Инициализация ввода
    Input::Initialize(mWindow->GetWindowPointer());

    // Инициализация рендера
    Render::Renderer::Initialize();

    mPreviousTime = glfwGetTime();

}

void Core::Application::EventHandler(const Core::Event& event)
{
    for (auto& layer : mLayerStack.GetLayers())
    {
        layer->EventHandler(event);
    }
}

void Core::Application::Start() {

    Log::Info("Application running");

    // Ограничиваем FPS до 60
    const double dt = 1 / (double)60;

    // Лаг
    double lag = 0;

    // Количество кадров за 1 секунду
    unsigned int frames = 0;

    // Время на один кадр
    double frameTime = 0;

    // Игровой цикл
    while ((mIsRunning = mWindow->Exec())) {

        // Получаем текущее время и находим дельту
        double currentTime = glfwGetTime();
        double elapsed     = currentTime - mPreviousTime;

        mPreviousTime = currentTime;
        lag += elapsed;
        frameTime += elapsed;

        // Обновляем игру до тех пор, пока лаг не станет меньше 1 мс
        while (lag >= dt) {

            for (auto* pLayer : mLayerStack.GetLayers()) {
                pLayer->OnUpdate();
            }

            lag -= dt;
        }

        // Интерполируем разницу между кадрами (получаем более плавное значение)
        const double interpolate = lag / dt;

        // Render frame
        for (auto* pLayer : mLayerStack.GetLayers()) {
            pLayer->OnRender(interpolate);
        }

        // Render UI
        mLayerStack.GetOverlay()->OnBegin();
        for (auto* pLayer : mLayerStack.GetLayers()) {

            pLayer->OnUIRender();
        }
        mLayerStack.GetOverlay()->OnEnd();

        mWindow->SwapBuffers();
        mWindow->Update();

        // Увеличиваем счётчик кадров
        frames++;

        // Если время кадра больше 1 секунды, обнуляем счётчик кадров и время
        if (frameTime >= 1.0) {
            std::string fpsWindowTitle = std::string("KitEngine") + std::string(" FPS: ") + std::to_string(frames);
            mWindow->SetWindowTitle(fpsWindowTitle);

            frames = 0;
            frameTime = 0;
        }
    }

    Log::Info("Application stopped");

}

void Core::Application::Close() {
    glfwSetWindowShouldClose(mWindow->GetWindowPointer(), GLFW_TRUE);
}

Core::Application::Application()
    : mIsRunning(false), mPreviousTime(0) {

}


