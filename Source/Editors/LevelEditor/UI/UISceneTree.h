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

        template<typename T>
        void SceneTree(const char* pNodeName, const std::vector<T>& objects)
        {
            auto& level = GameLevel::Get();
            if (ImGui::TreeNodeEx(pNodeName, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow)) 
            {
                for (auto& object : objects)
                {
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
                    flags |= level.GetSelectedObject() == object.get() ? ImGuiTreeNodeFlags_Selected : 0;

                    if (ImGui::TreeNodeEx(object->GetName().c_str(), flags))
                    {
                        if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                            level.SetSelectedObject(object.get());
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
    };
}