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

            // Проверяем, что мышка попадает в область вьюпорта
            const glm::vec2& mousePosition = Core::Input::mousePosition;
            if (mousePosition.x >= vMin.x && mousePosition.x <= vMax.x
                && mousePosition.y >= vMin.y && mousePosition.y <= vMax.y)
            {
                // Если была нажата левая кнопка мыши
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) 
                {
                    // Получаем координаты курсора относительно вьюпорта
                    glm::vec2 relative_mouse_position(
                        mousePosition.x - ImGui::GetCursorScreenPos().x - ImGui::GetScrollX(),
                        mousePosition.y - ImGui::GetCursorScreenPos().y - ImGui::GetScrollY()
                    );

                    // Переводим экранные координаты в мировые координаты
                    glm::vec3 origin, direction;
                    EditorCamera::Instance().ScreenToWorldPoint(relative_mouse_position, glm::vec2(mWidth, mHeight), origin, direction);
                    origin = EditorCamera::Instance().GetPos();
                    
                    glm::vec3 end = origin + direction * 1000.0f;
                    btRigidBody* pRigidBody = PhysicSystem::Instance().GetPickBody(origin, end);
                    if (pRigidBody != nullptr) {
                        std::cout << "SELECTED OBJECT\n"; 
                    }
                    DEBUG_MSG("PICK POINT - x: %.3f, y: %.3f, z: %.3f", end.x, end.y, end.z); 
                }
            }

            // // Проверяем клик
            // if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            //     // Получаем координаты курсора относительно вьюпорта
            //     glm::vec2 relative_mouse_position(
            //         Core::Input::mousePosition.x - ImGui::GetCursorScreenPos().x - ImGui::GetScrollX(),
            //         Core::Input::mousePosition.y - ImGui::GetCursorScreenPos().y - ImGui::GetScrollY()
            //     );
            //     DEBUG_MSG("Pre - x: %.3f, y: %.3f", relative_mouse_position.x, relative_mouse_position.y);                
            // }

            ImGui::Image(RenderBackend::Get().GetFrame(), ImVec2(mWidth, mHeight), ImVec2(0,1), ImVec2(1,0));
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                
                // // Получаем координаты курсора относительно вьюпорта
                // glm::vec2 relative_mouse_position(
                //     Core::Input::mousePosition.x - ImGui::GetCursorScreenPos().x - ImGui::GetScrollX(),
                //     Core::Input::mousePosition.y - ImGui::GetCursorScreenPos().y - ImGui::GetScrollY()
                // );
                // DEBUG_MSG("Pre - x: %.3f, y: %.3f", relative_mouse_position.x, relative_mouse_position.y);

                // // Переводим экранные координаты курсора в мировые координаты
                // glm::vec3 origin, direction;
                // EditorCamera::Instance().ScreenToWorldPoint(relative_mouse_position, glm::vec2(mWidth, mHeight), origin, direction);

                // glm::vec3 end = origin + direction * 1000.0f;
                // btRigidBody* pRigidBody = PhysicSystem::Instance().GetPickBody(origin, end);
                // if (pRigidBody != nullptr) {
                //     std::cout << "SELECTED OBJECT\n"; 
                // }
                // DEBUG_MSG("PICK POINT - x: %.3f, y: %.3f, z: %.3f", origin.x, origin.y, origin.z);
            }

            // Если размеры вьюпорта изменились, меняем размеры буфера кадра
            int width  = vMax.x - vMin.x;
            int height = vMax.y - vMin.y;
            if (mWidth != width || mHeight != height) {
                mWidth = width;
                mHeight = height;
                RenderBackend::Get().Resize(mWidth, mHeight, ImGui::GetCursorScreenPos().x - 200, ImGui::GetCursorScreenPos().y);
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