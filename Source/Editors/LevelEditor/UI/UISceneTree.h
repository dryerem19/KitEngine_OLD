#pragma once

#include "Core/KitUI.h"

namespace LevelEditor
{
    class UISceneTree : public KitUI
    {
    public:
        UISceneTree() = default;
        UISceneTree(IController* controller) : KitUI(controller) { }
        void Draw() override;
        Render::KitModel mNanoModel;
        Render::KitScene mScene;

        Render::KitObject mSelectedObject;
        bool isModelLoaded = false;

        void SceneTree();
        void DrawNode(Render::KitTransform& tr);
    };
}