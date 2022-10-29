//
// Created by dryerem19 on 10/28/22.
//

#ifndef LEVELEDITOR_APPLICATION_H
#define LEVELEDITOR_APPLICATION_H

#include "KitEnginePch.h"
#include "Core/Window.h"

#include "Graphics/Renderer.h"
using namespace KitEngine::Graphics;

namespace KitEngine::Core
{
    class Application
    {
    private:
        std::unique_ptr<Window> mWindow;
        Renderer mRenderer;
        double mPreviousTime;
        bool mIsRunning;

    public:
        Application(const Application&) = delete;
        Application& operator=(Application&) = delete;
        static Application& Instance();

        [[nodiscard]] inline auto& GetWindow() const { return mWindow; }
        void virtual Start(const KitEngine::WindowProps& props);

    protected:
        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnRender(double dt);

    private:
        Application();
        ~Application() = default;
    };
}

#endif //LEVELEDITOR_APPLICATION_H
