#pragma once


#include "Core/KitUI.h"
#include "Entity.h"
#include "GameLevel.h"
#include "KitLight.h"

namespace LevelEditor
{
    class UISceneTree : public KitUI
    {
    public:
        UISceneTree() = default;
        UISceneTree(IController* controller) : KitUI(controller) { }
        void Draw() override;

        bool isModelLoaded = false;

        void SceneTree();
    };
}