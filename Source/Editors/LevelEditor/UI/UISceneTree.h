#pragma once


#include "Core/KitUI.h"
#include "SceneManager.h"

namespace LevelEditor
{
    class UISceneTree : public KitUI
    {
    private:
        std::unordered_map<std::string, std::pair<Core::BaseEntity*, int>> mSceneNames; 
    public:
        UISceneTree() = default;
        UISceneTree(IController* controller) : KitUI(controller) { }
        void Draw() override;

        bool isModelLoaded = false;

        void SceneTree();
        void DrawNode(Core::BaseEntity* pEntity);    
    };
}