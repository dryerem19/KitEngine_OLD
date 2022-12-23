#include "UIViewport.h"

namespace LevelEditor
{
    void UIViewport::Draw()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3.0f,3.0f));
        
        ImGui::Begin("Viewport", 0, ImGuiWindowFlags_NoScrollbar);
        {
            ImVec2 vMin = ImGui::GetWindowContentRegionMin();
            ImVec2 vMax = ImGui::GetWindowContentRegionMax();
            vMin.x += ImGui::GetWindowPos().x;
            vMin.y += ImGui::GetWindowPos().y;
            vMax.x += ImGui::GetWindowPos().x;
            vMax.y += ImGui::GetWindowPos().y;

            ImGui::Image(RenderBackend::Get().GetFrame(), ImVec2(mWidth, mHeight), ImVec2(0,1), ImVec2(1,0));
            // if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            //     auto pos = RenderBackend::Get().GetCursor3d().GetPickPoint(EditorCamera::Instance(), 
            //         glm::vec2(mWidth, mHeight));
            //     DEBUG_MSG("PICK POINT - x: %.3f, y: %.3f, z: %.3f", pos.x, pos.y, pos.z);
            // }

            // Если размеры вьюпорта изменились, меняем размеры буфера кадра
            int width  = vMax.x - vMin.x;
            int height = vMax.y - vMin.y;
            if (mWidth != width || mHeight != height) {
                mWidth = width;
                mHeight = height;
                RenderBackend::Get().Resize(mWidth, mHeight);
                EditorCamera::Instance().UpdateAspect((float)mWidth / mHeight);
            }

            // Принимаем данные, которые пользователь перетащил на вьюпорт
            if(ImGui::BeginDragDropTarget()) {
                auto payload = ImGui::AcceptDragDropPayload("Item_content_browser", 
                    ImGuiDragDropFlags_AcceptBeforeDelivery);

                if (payload != nullptr) {
                    std::string* filepath = (std::string*)payload->Data;
                    if (filepath != nullptr) {

                        glm::vec3 pickRay = RenderBackend::Get().GetCursor3d().GetPickRay(EditorCamera::Instance(), 
                            glm::vec2(mWidth, mHeight));
                        glm::vec3 cameraPos = EditorCamera::Instance().GetPos();

                        if (mIsFirstDelivery) {
                            pDeliveryEntity = GameLevel::Get().CreateEntity();
                            pDeliveryEntity->SetModel(Core::ResourceManager::Instance().GetModel(*filepath));
                            pDeliveryEntity->SetName(pDeliveryEntity->GetModel()->mName);

                            cameraPos += pickRay * mCameraMouseDistance;
                            pDeliveryEntity->transform.SetPosition(cameraPos);
                            mIsFirstDelivery = false;
                        } else {
                            if (pDeliveryEntity != nullptr && mMousePickRay != pickRay) {
                                mMousePickRay = pickRay;

                                const glm::vec2& mouseOffset = Core::Input::mouseOffset;
                                glm::vec3 entityPos = pDeliveryEntity->transform.GetPosition();
                                entityPos.x += mouseOffset.x * mMoveSpeed;
                                entityPos.z += mouseOffset.y * mMoveSpeed;
                                pDeliveryEntity->transform.SetPosition(entityPos);
                            }
                        }

                        if (payload->IsDelivery()) {
                            mMousePickRay.x = mMousePickRay.y = mMousePickRay.z = 0;
                            mIsFirstDelivery = true;
                        }
                    }
                }
                ImGui::EndDragDropTarget();
            }

            // Draw Gizmo

            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, mWidth, mHeight);
            DrawGizmo();
        } 
        ImGui::End();
        ImGui::PopStyleVar();
    };

    void UIViewport::DrawGizmo()
    {
        const auto& level = GameLevel::Get();
        auto selected = level.GetSelectedObject();
        if (selected && mOperation != GizmoOperation::NONE)
        {
            Transform& transform = selected->transform;

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