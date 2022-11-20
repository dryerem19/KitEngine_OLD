//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_TESTLAYER_H
#define KITENGINE_TESTLAYER_H

#include <memory>

#include <fmt/format.h>
#include <Events/FrameBufferResizeEvent.h>
#include <Events/WindowResizeEvent.h>
#include <BaseLayer.h>
#include <Window.h>

#include "Core/EditorCamera.h"

#include "KitUI.h"
#include "UITopMainMenu.h"
#include "UITopBarTools.h"
#include "UISceneTree.h"
#include "UIViewport.h"

using namespace LevelEditor;

namespace UI
{
    class UILayer : public Core::BaseLayer
    {
    private:
          
        std::unique_ptr<Render::Shader> mShader;
        glm::mat4 mTransform;

    public:
        UILayer() = default;

        void OnStart() override;
        void OnUpdate() override;
        void EventHandler(const Core::Event& event) override;
        void OnRender(double dt) override;
        void OnUIRender() override;
        void OnFinish() override;

        Render::FrameBuffer frameBuffer;
        

        // UI Window
        UITopMainMenu uiTopMainMenu;
        UITopBarTools uiTopBarTools;
        UISceneTree   uiSceneTree;
        UIViewport    uiViewport;
        void Docking();
    };
}

#endif //KITENGINE_TESTLAYER_H
