#pragma once

#include "Core/KitUI.h"
#include "UIFileDialog.h"

#include "SceneManager.h"
#include "UISceneTree.h"

namespace LevelEditor
{
    class UITopMainMenu : public KitUI
    {
    public:
        bool isCheckFileDialog = false;
        UITopMainMenu() = default;
        UITopMainMenu(IController* controller) : KitUI(controller) { }
        void Draw() override;

        void OnLoadModel(std::string* filepath);
        void ShowAbout(bool* close);

        UISceneTree* uiSceneTree;
    };
}