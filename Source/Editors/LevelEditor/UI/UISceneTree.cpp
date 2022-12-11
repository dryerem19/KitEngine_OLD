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
        auto& level = GameLevel::Get();
        if (ImGui::TreeNodeEx("Entities", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto& entity : level.mEntities)
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                flags |= GameLevel::Get().GetSelectedEntity() == entity
                    ? ImGuiTreeNodeFlags_Selected : 0;
                if (ImGui::TreeNodeEx(entity->GetModel()->mName.c_str(), flags))
                {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                    {
                        GameLevel::Get().SetSelectedEntity(entity);
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        if(ImGui::TreeNodeEx("Lights", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto& light : level.mKitLights)
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                //flags |= GameLevel::Get().GetSelectedEntity() == light
                //    ? ImGuiTreeNodeFlags_Selected : 0;
                if (ImGui::TreeNodeEx("light", flags))
                {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                    {
                        //GameLevel::Get().SetSelectedEntity(light);
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }
}

