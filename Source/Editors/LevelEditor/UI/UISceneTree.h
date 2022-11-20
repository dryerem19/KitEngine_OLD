#pragma once

#include "KitUI.h"

namespace UI
{
    class UISceneTree : public KitUI
    {
    public:
        UISceneTree() = default;
        void Draw() override;
        Render::KitModel mNanoModel;
        Render::KitScene mScene;

        Render::KitObject mSelectedObject;
        bool isModelLoaded = false;

        void SceneTree();
        void DrawNode(Render::KitTransform& tr);
    };
}