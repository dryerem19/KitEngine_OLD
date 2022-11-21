#pragma once


#include "Core/KitUI.h"
#include "SceneManager.h"


namespace LevelEditor
{
    class UISceneTree : public KitUI
    {
    public:
        UISceneTree() = default;
        UISceneTree(IController* controller) : KitUI(controller) { }
        void Draw() override;
        Render::KitModel mNanoModel;
        bool isModelLoaded = false;

        void SceneTree();
        void DrawNode(Render::KitTransform& tr);
    };
}