#include "UIViewport.h"

namespace LevelEditor
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

            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
            DrawGizmo();
        } 
        ImGui::End();
        ImGui::PopStyleVar();
    };

    void UIViewport::DrawGizmo()
    {
        const auto& level = Render::GameLevel::Get();
        auto selected = level.GetSelectedEntity();
        if (selected && mOperation != GizmoOperation::NONE)
        {
            Transform& transform = selected->GetTransform();

            glm::vec3 position = transform.GetPosition();
            glm::vec3 rotation = glm::degrees(transform.GetRotation());
            glm::vec3 scale = transform.GetScale();

            /* Build transform matrix */
            float transformMatrix[16];
            ImGuizmo::RecomposeMatrixFromComponents(&position.x, &rotation.x, &scale.x, transformMatrix);
            ImGuizmo::Manipulate(EditorCamera::Instance().GetView(), EditorCamera::Instance().GetPerspective(), (ImGuizmo::OPERATION)mOperation, ImGuizmo::MODE::LOCAL, transformMatrix);
            
            /* If we moved the manipulator */
            if (ImGuizmo::IsUsing())
            {
                ImGuizmo::DecomposeMatrixToComponents(transformMatrix, &position.x, &rotation.x, &scale.x);
                switch (mOperation)
                {
                case GizmoOperation::TRANSLATE:
                    transform.SetPosition(position);
                    break;
                case GizmoOperation::ROTATE:
                    {
                        transform.SetRotation(glm::radians(rotation));
                    }
                    break;
                case GizmoOperation::SCALE:
                    transform.SetScale(scale);
                    break;
                default:
                    break;
                }
            }
        }
    }
}