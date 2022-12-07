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
        for (auto&& obj : level)
        {
            DrawNode(obj.second.get());
        }
    }

    void UISceneTree::DrawNode(GameObject* pEntity)
    {
        assert( pEntity && "Entity must not be nullptr!" );

        ImGuiTreeNodeFlags flags = !pEntity->HasChilds() ? ImGuiTreeNodeFlags_Leaf : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= (pEntity == Render::GameLevel::Get().GetSelectedEntity()) ? ImGuiTreeNodeFlags_Selected : 0;        

        bool isNodeOpen = false;
        if (isNodeOpen = ImGui::TreeNodeEx(pEntity->GetName().c_str(), flags))
        {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                Render::GameLevel::Get().SetSelectedEntity(pEntity);
            }

            for (uint32_t iChild = 0; iChild < pEntity->GetCountOfChilds(); iChild++)
            {
                DrawNode(pEntity->GetChildByIndex(iChild));
            }
            
            ImGui::TreePop();
        }

        if (!isNodeOpen && ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            Render::GameLevel::Get().SetSelectedEntity(pEntity);
        }
    }
}

