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
        auto& scene_manager = Render::SceneManager::Instance();
        auto view = scene_manager.GetCurrentScene()->View<Render::KitTransform>();
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
        auto& scene_manager = Render::SceneManager::Instance();
        auto obj = scene_manager.GetCurrentScene()->GetObject(tr);
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

        // Проверяем нажатие на элемент дерева
        if (ImGui::IsItemClicked())
        {
            // Устанавливаем выбранный объект текущей сцены
            scene_manager.GetCurrentScene()->SetSelectedObject(obj);
        }
    }
}

