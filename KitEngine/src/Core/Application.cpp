//
// Created by dryerem19 on 10/28/22.
//
#include "Core/Application.h"
#include "Core/Logger.h"

//------------------------------------------------------------------------------------
// PUBLIC SECTION
//------------------------------------------------------------------------------------

KitEngine::Core::Application::Application() {

    mIsRunning = true;
    mPreviousTime = glfwGetTime();

}

void KitEngine::Core::Application::Start(const KitEngine::WindowProps& props) {

    Log::Info("Application running");

    mWindow = std::make_unique<Window>(props);
    if (!mWindow->Initialize()) {
        Log::Critical("Failed to create the window!");
        exit(-1);
    }

    // Запускается при старте приложения
    this->OnStart();

    // Ограничиваем FPS до 60
    const double dt = 1 / (double)60;

    // Лаг
    double lag = 0;

    // Количество кадров за 1 секунду
    unsigned int frames = 0;

    // Время на один кадр
    double frameTime = 0;

    // Игровой цикл
    while (mIsRunning) {
        mIsRunning = mWindow->Exec();

        // Получаем текущее время и находим дельту
        double currentTime = glfwGetTime();
        double elapsed     = currentTime - mPreviousTime;

        mPreviousTime = currentTime;
        lag += elapsed;
        frameTime += elapsed;

        // Обновляем игру до тех пор, пока лаг не станет меньше 1 мс
        while (lag >= dt) {
            this->OnUpdate();
            lag -= dt;
        }

        // Интерполируем разницу между кадрами (получаем более плавное значение)
        const double interpolate = lag / dt;

        // Рисуем игру
        this->OnRender(interpolate);
        mWindow->SwapBuffers();

        // Увеличиваем счётчик кадров
        frames++;

        // Если время кадра больше 1 секунды, обнуляем счётчик кадров и время
        if (frameTime >= 1.0) {
            std::string fpsWindowTitle = mWindow->GetProps().Title + " FPS: " + std::to_string(frames);
            mWindow->SetWindowTitle(fpsWindowTitle);

            frames = 0;
            frameTime = 0;
        }
    }

    Log::Info("Application stopped");

}


//------------------------------------------------------------------------------------
// PRIVATE SECTION
//------------------------------------------------------------------------------------

void KitEngine::Core::Application::OnStart() {

}

void KitEngine::Core::Application::OnUpdate() {

    mWindow->Update();

}

void KitEngine::Core::Application::OnRender(double dt) {

    mRenderer.Clear();

}
