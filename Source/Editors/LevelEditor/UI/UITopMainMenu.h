#pragma once

#include "KitUI.h"
#include "UIFileDialog.h"

#include "UISceneTree.h"

namespace UI
{
    class UITopMainMenu : public KitUI
    {
    public:
        bool isCheckFileDialog = false;
        UITopMainMenu() = default;
        void Draw() override;

        void OnLoadModel(std::string* filepath);
        void ShowAbout(bool* close);

        UISceneTree* uiSceneTree;
    };
}