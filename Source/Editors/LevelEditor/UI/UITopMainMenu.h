#pragma once

#include "Core/KitUI.h"
#include "UIFileDialog.h"

#include "GameLevel.h"
#include "Entity.h"
#include "UISceneTree.h"
#include "ResourceManager.h"
#include "MeshVisualImporter.h"

namespace LevelEditor
{
    class UITopMainMenu : public KitUI
    {
    public:
        UITopMainMenu() = default;
        UITopMainMenu(IController* controller) : KitUI(controller) { }
        void Draw() override;

        void OnLoadModel(std::string* filepath);
        void ShowAbout(bool* close);

        UISceneTree* uiSceneTree;
    };
}