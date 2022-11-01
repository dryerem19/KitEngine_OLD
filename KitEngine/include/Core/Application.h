//
// Created by dryerem19 on 10/28/22.
//

#ifndef LEVELEDITOR_APPLICATION_H
#define LEVELEDITOR_APPLICATION_H

#include "KitEnginePch.h"
#include "Core/Window.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"

#include "Graphics/Renderer.h"
using namespace KitEngine::Graphics;

namespace KitEngine::Core
{
    class Application
    {
    private:
        std::unique_ptr<Window> mWindow;
        LayerStack mLayerStack;
        std::shared_ptr<ImGuiLayer> mImguiLayer;
        double mPreviousTime;
        bool mIsRunning;

    public:
        Application(const Application&) = delete;
        Application& operator=(Application&) = delete;

        static Application& Instance();
        void PushLayer(const std::shared_ptr<BaseLayer> layer);
        void PopLayer(const std::shared_ptr<BaseLayer> layer);
        [[nodiscard]] inline auto& GetWindow() const { return mWindow; }
        void virtual Start(const KitEngine::WindowProps& props);

    private:
        Application();
        ~Application();
    };
}

#endif //LEVELEDITOR_APPLICATION_H
