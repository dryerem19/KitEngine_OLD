#include "UISceneTree.h"

namespace LevelEditor
{
    void UISceneTree::Draw()
    {
        ImGui::Begin("Scene Tree");
        {
            SceneTree();
        }
        ImGui::End();
    }

    void UISceneTree::SceneTree()
    {
        auto& level = Render::GameLevel::Get();
        if (ImGui::TreeNodeEx("Entities", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto& entity : level.mEntities)
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                flags |= Render::GameLevel::Get().GetSelectedEntity() == entity
                    ? ImGuiTreeNodeFlags_Selected : 0;
                if (ImGui::TreeNodeEx(entity->GetModel()->mName.c_str(), flags))
                {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                    {
                        Render::GameLevel::Get().SetSelectedEntity(entity);
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }
}

