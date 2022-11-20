#include "UIViewport.h"



namespace UI
{
    void UIViewport::Draw()
    {
        uint32_t backTexture = frameBuffer->GetTextureRenderID();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::Begin("Viewport");
        {
            ImVec2 vMin = ImGui::GetWindowContentRegionMin();
            ImVec2 vMax = ImGui::GetWindowContentRegionMax();
            vMin.x += ImGui::GetWindowPos().x;
            vMin.y += ImGui::GetWindowPos().y;
            vMax.x += ImGui::GetWindowPos().x;
            vMax.y += ImGui::GetWindowPos().y;
            ImGui::GetWindowDrawList()->AddImage((ImTextureID)backTexture, vMin, vMax, ImVec2(0,1), ImVec2(1,0));
            // Draw Gizmo
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
            DrawGizmo();
        } 
        ImGui::End();
        ImGui::PopStyleVar();
    };

    void UIViewport::DrawGizmo()
    {
        if (uiSceneTree->mSelectedObject)
        {
            auto& transform = uiSceneTree->mSelectedObject->mTransform;
            float translationComponent[3] = 
            { 
                transform.Translation.x,
                transform.Translation.y,
                transform.Translation.z
            };

            float rotationComponent[3] =
            { 
                transform.Rotation.x,
                transform.Rotation.y,
                transform.Rotation.z
            };

            float scaleComponent[3] =
            { 
                transform.Scale.x,
                transform.Scale.y,
                transform.Scale.z
            };

            /* Build transform matrix */
            float transformMatrix[16];
            ImGuizmo::RecomposeMatrixFromComponents(translationComponent, rotationComponent, scaleComponent, transformMatrix);
            ImGuizmo::Manipulate(EditorCamera::Instance().GetView(), EditorCamera::Instance().GetPerspective(), uiTopBarTools->mode, ImGuizmo::MODE::LOCAL, transformMatrix);

            /* If we moved the manipulator */
            if (ImGuizmo::IsUsing())
            {
                /* We get new transformed components */
                float translationComponent[3] = {}, rotationComponent[3] = {}, scaleComponent[3] = {};
                ImGuizmo::DecomposeMatrixToComponents(transformMatrix, translationComponent, rotationComponent, scaleComponent);

                /* Restore the new transformed components */
                transform.Translation = 
                {
                    translationComponent[0],
                    translationComponent[1],
                    translationComponent[2]
                };
                transform.Rotation =
                {
                    rotationComponent[0], 
                    rotationComponent[1], 
                    rotationComponent[2]
                };
                transform.Scale =
                {
                    scaleComponent[0],
                    scaleComponent[1],
                    scaleComponent[2]
                };
            }
        }
    }
}