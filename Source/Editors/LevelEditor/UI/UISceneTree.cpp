#include "UISceneTree.h"

namespace LevelEditor
{
    void UISceneTree::Draw()
    {
        ImGui::Begin("Scene Tree");
        {
            auto& level = GameLevel::Get();
            SceneTree("Objects", level._objects);
            SceneTree("Lights", level._lights);
            SceneTree("Sounds", level._soundsources);
        }
        ImGui::End();
    }
}

