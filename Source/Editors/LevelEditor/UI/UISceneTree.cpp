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
        if (ImGui::TreeNodeEx("Objects", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto& object : level._objects)
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                flags |= GameLevel::Get().GetSelectedObject() == object.get()
                    ? ImGuiTreeNodeFlags_Selected : 0;
                if (ImGui::TreeNodeEx(object->GetName().c_str(), flags))
                {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                    {
                        GameLevel::Get().SetSelectedObject(object.get());
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        if(ImGui::TreeNodeEx("Lights", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow))
        {
            for (auto& light : level._lights)
            {
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                flags |= GameLevel::Get().GetSelectedObject() == light.get()
                   ? ImGuiTreeNodeFlags_Selected : 0;
                if (ImGui::TreeNodeEx(light->GetName().c_str(), flags))
                {
                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                    {
                        GameLevel::Get().SetSelectedObject(light.get());
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
    }
}

