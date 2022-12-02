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
        //auto& scene_manager = Render::SceneManager::Instance();
        // auto view = scene_manager.GetCurrentScene()->View<Render::KitTransform>();
        // for (auto [entity, tr] : view.each())
        // {
        //     if (nullptr == tr.pParent) 
        //     {
        //         this->DrawNode(tr);
        //     }
        // }

        auto& world = Render::World::Get();
        DrawNode(world.GetSelf());

    }

    void UISceneTree::DrawNode(Core::BaseEntity* pEntity)
    {
        assert( pEntity && "Entity must not be nullptr!" );

        ImGuiTreeNodeFlags flags = !pEntity->HasChilds() ? ImGuiTreeNodeFlags_Leaf : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= (pEntity == Render::World::Get().GetSelectedEntity()) ? ImGuiTreeNodeFlags_Selected : 0;        

        if (mSceneNames.find(pEntity->GetName()) != mSceneNames.end())
        {
            auto& value = mSceneNames[pEntity->GetName()];
            if (value.first != pEntity)
            {
                value.second++;
                pEntity->SetName(pEntity->GetName() + "_" + std::to_string(value.second));
            }
        }
        else
        {
            mSceneNames.insert({pEntity->GetName(), std::make_pair(pEntity, 0)});
        }

        bool isNodeOpen = false;
        if (isNodeOpen = ImGui::TreeNodeEx(pEntity->GetName().c_str(), flags))
        {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                Render::World::Get().SetSelectedEntity(pEntity);
            }

            for (uint32_t iChild = 0; iChild < pEntity->GetCountOfChilds(); iChild++)
            {
                DrawNode(pEntity->GetChildByIndex(iChild));
            }
            
            ImGui::TreePop();
        }

        if (!isNodeOpen && ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            Render::World::Get().SetSelectedEntity(pEntity);
        }
    }
    // void UISceneTree::DrawNode(Render::KitTransform& tr)
    // {
    //     auto& scene_manager = Render::SceneManager::Instance();
    //     auto obj = scene_manager.GetCurrentScene()->GetObject(tr);
    //     auto& tc = obj.GetComponent<Render::KitTag>();

    //     ImGuiTreeNodeFlags flags = tr.mChildren.empty() 
    //             ? ImGuiTreeNodeFlags_Leaf : 0;
    //     flags |= ImGuiTreeNodeFlags_OpenOnArrow;   
    //     flags |= (obj == scene_manager.GetSelectedObject()) ? ImGuiTreeNodeFlags_Selected : 0;

    //     if (ImGui::TreeNodeEx(tc.Tag.c_str(), flags))
    //     {
    //         for (auto&& child : tr.mChildren)
    //         {
    //             this->DrawNode(*child);
    //         }

    //         ImGui::TreePop();
    //     }

    //     // Проверяем нажатие на элемент дерева
    //     if (ImGui::IsItemClicked())
    //     {
    //         // Устанавливаем выбранный объект текущей сцены
    //         scene_manager.SetSelectedObject(obj);
    //     }
    // }
}

