#include "UISceneTree.h"

namespace UI
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
        auto view = mScene.View<Render::KitTransform>();
        for (auto [entity, tr] : view.each())
        {
            if (nullptr == tr.pParent) 
            {
                this->DrawNode(tr);
            }
        }
    }

    void UISceneTree::DrawNode(Render::KitTransform& tr)
    {
        auto obj = mScene.GetObject(tr);
        auto& tc = obj.GetComponent<Render::KitTag>();

        ImGuiTreeNodeFlags flags = tr.mChildren.empty() 
                ? ImGuiTreeNodeFlags_Leaf : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;    
        flags |= obj == mSelectedObject ? ImGuiTreeNodeFlags_Selected : 0;
        if (ImGui::TreeNodeEx(tc.Tag.c_str(), flags))
        {
            for (auto&& child : tr.mChildren)
            {
                this->DrawNode(*child);
            }

            ImGui::TreePop();
        }

        if (ImGui::IsItemClicked())
        {
            mSelectedObject = obj;
        }
    }
}

