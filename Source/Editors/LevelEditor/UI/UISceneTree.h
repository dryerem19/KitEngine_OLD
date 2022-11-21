#pragma once

#include "KitUI.h"
#include "SceneManager.h"

namespace UI
{
    class UISceneTree : public KitUI
    {
    public:
        UISceneTree() = default;
        void Draw() override;
        Render::KitModel mNanoModel;
        bool isModelLoaded = false;

        void SceneTree();
        void DrawNode(Render::KitTransform& tr);
    };
}