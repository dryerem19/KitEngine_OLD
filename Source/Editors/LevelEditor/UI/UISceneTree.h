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
        std::shared_ptr<Render::KitObject> mSelectedObject;
        bool isModelLoaded = false;

        void SceneTree();
    };
}