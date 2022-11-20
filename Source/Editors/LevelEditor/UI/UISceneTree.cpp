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
        if(isModelLoaded)
        {
            if(ImGui::TreeNode(mNanoModel.mName.c_str()))
            {
                for(auto& mesh : mNanoModel)
                {
                    ImGuiTreeNodeFlags flags = mesh->mChildren.empty() ? ImGuiTreeNodeFlags_Leaf : 0;
                    if(ImGui::TreeNodeEx(fmt::format("{}\t{}", ICON_FA_CUBE, mesh->mName).c_str(), flags))
                    {
                        ImGui::TreePop();
                    }

                    if (ImGui::IsItemClicked()) {
                        mSelectedObject = mesh;
                    }
                }
                ImGui::TreePop();
            }

            if (ImGui::IsItemClicked()) {
                mSelectedObject = static_cast<std::shared_ptr<Render::KitObject>>(&mNanoModel);
            }
        }
    }
}

