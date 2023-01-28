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

            ImVec2 viewportSize = ImGui::GetContentRegionAvail();

            // Если размеры вьюпорта изменились, меняем размеры буфера кадра
            int width  = vMax.x - vMin.x;
            int height = vMax.y - vMin.y;
            if (mWidth != width || mHeight != height) {
                mWidth = width;
                mHeight = height;
                RenderBackend::Get().Resize(mWidth, mHeight, 0, 0);
                EditorCamera::Instance().SetViewportSize(mWidth, mHeight);
            }            

            const glm::vec2& mousePosition = Core::Input::mousePosition;
            glm::vec2 relative_mouse_position(
                mousePosition.x - ImGui::GetCursorScreenPos().x - ImGui::GetScrollX(),
                mousePosition.y - ImGui::GetCursorScreenPos().y - ImGui::GetScrollY()
            );       
             

            if (ImGui::IsWindowHovered())
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    glm::vec3 rayDirection = EditorCamera::Instance().CreateRay(relative_mouse_position, glm::vec2(mWidth, mHeight));
                    glm::vec3 rayStartPosition = EditorCamera::Instance().GetPosition();
                    glm::vec3 rayEndPosition = rayStartPosition + rayDirection * 1000.0f;  

                    btRigidBody* pRigidBody = PhysicSystem::Instance().GetPickBody(rayStartPosition, rayEndPosition);
                    if (pRigidBody)
                    {
                        PhysicObject* phObject = static_cast<PhysicObject*>(pRigidBody->getUserPointer());
                        phObject->HasKitObject() ? phObject->GetKitObject()->OnPicked() : (void)0;
                    }     
                    else 
                    {
                        //GameLevel::Get().SetSelectedObject(nullptr);
                    }                    
                }
            }

            ImGui::Image(RenderBackend::Get().GetFrame(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));
            //if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                
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
            //}

            // Принимаем данные, которые пользователь перетащил на вьюпорт
            if(ImGui::BeginDragDropTarget()) {
                auto payload = ImGui::AcceptDragDropPayload("Item_content_browser", 
                    ImGuiDragDropFlags_AcceptBeforeDelivery);

                if (payload != nullptr) {
                    std::string* filepath = (std::string*)payload->Data;
                    if (filepath != nullptr) {

                        // glm::vec3 pickRay = RenderBackend::Get().GetCursor3d().GetPickRay(EditorCamera::Instance(), 
                        //     glm::vec2(mWidth, mHeight));
                        // glm::vec3 cameraPos = EditorCamera::Instance().GetPosition();

                        // glm::vec3 rayDirection = EditorCamera::Instance().CreateRay(relative_mouse_position, glm::vec2(mWidth, mHeight));
                        // glm::vec3 rayStartPosition = EditorCamera::Instance().GetPosition();
                        // glm::vec3 rayEndPosition = rayStartPosition + rayDirection * mCameraMouseDistance;                          

                        if (mIsFirstDelivery) {
                            pDeliveryEntity = GameLevel::Get().CreateEntity();
                            pDeliveryEntity->SetModel(Core::ResourceManager::Instance().GetModel(filepath->c_str()));
                            pDeliveryEntity->SetName(pDeliveryEntity->GetModel()->mName);

                            //cameraPos += pickRay * mCameraMouseDistance;
                            //pDeliveryEntity->transform.SetPosition(rayEndPosition);

                            glm::vec3 rayDirection = EditorCamera::Instance().CreateRay(relative_mouse_position, glm::vec2(mWidth, mHeight));
                            glm::vec3 rayStartPosition = EditorCamera::Instance().GetPosition();
                            glm::vec3 rayEndPosition = rayStartPosition + rayDirection * mCameraMouseDistance;  
                            //pDeliveryEntity->transform.SetPosition(rayEndPosition); 

                            mIsFirstDelivery = false;
                        } else {
                            if (pDeliveryEntity != nullptr) {
                                // glm::vec3 rayDirection = EditorCamera::Instance().CreateRay(relative_mouse_position, glm::vec2(mWidth, mHeight));
                                // glm::vec3 rayStartPosition = EditorCamera::Instance().GetPosition();
                                // glm::vec3 rayEndPosition = rayStartPosition + rayDirection * mCameraMouseDistance;     

                                // const glm::vec2& mouseOffset = Core::Input::mouseOffset;
                                // rayEndPosition.x += mouseOffset.x;
                                // rayEndPosition.z += mouseOffset.y;                                

                                 //pDeliveryEntity->transform.SetPosition(rayEndPosition);                             
                                //mMousePickRay = rayEndPosition;

                                // const glm::vec2& mouseOffset = Core::Input::mouseOffset;
                                // glm::vec3 entityPos = pDeliveryEntity->transform.GetPosition();
                                // entityPos.x += mouseOffset.x * mMoveSpeed;
                                // entityPos.z += mouseOffset.y * mMoveSpeed;
                                // pDeliveryEntity->transform.SetPosition(entityPos);
                            }
                        }

                        if (payload->IsDelivery()) {
                            //mMousePickRay.x = mMousePickRay.y = mMousePickRay.z = 0;
                            mIsFirstDelivery = true;

                            // pDeliveryEntity = GameLevel::Get().CreateEntity();
                            // pDeliveryEntity->SetModel(Core::ResourceManager::Instance().GetModel(filepath->c_str()));
                            // pDeliveryEntity->SetName(pDeliveryEntity->GetModel()->mName);                            
                        }
                    }
                }
                ImGui::EndDragDropTarget();
            }

            // Draw Gizmo

            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(vMin.x, vMin.y, viewportSize.x, viewportSize.y);
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
            //Transform& objectTransform = selected->transform;


            glm::vec3 position = selected->transform.GetPosition();
            glm::vec3 rotation = selected->transform.GetRotation();
            glm::vec3 scale    = selected->transform.GetScale();
            
            glm::mat4 matrix;
            ImGuizmo::RecomposeMatrixFromComponents(&position.x, &rotation.x, &scale.x, glm::value_ptr(matrix));

            // glm::vec3 position, rotation, scaled;
            // glm::mat4 transformMatrix = selected->transform.GetModelMatrix();
            // ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transformMatrix), &position.x, &rotation.x, &scaled.x);

            const glm::mat4& viewMatrix = EditorCamera::Instance().GetView();
            const glm::mat4& projMatrix = EditorCamera::Instance().GetProjection();
            ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix), 
                (ImGuizmo::OPERATION)mOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(matrix));
            
            if (ImGuizmo::IsUsing())
            {
                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(matrix), &position.x, &rotation.x, &scale.x);

                selected->transform.SetPosition(position);
                selected->transform.SetRotation(rotation);
                

                //selected->transform.SetTransform(transformMatrix);
                if (selected->mPhysicObject)
                {
                    glm::vec3 centerOfMass = selected->mPhysicObject->GetPosition();
                    
                    glm::vec3 translation, rotationDecompose, scaledDecompose;
                    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(matrix), &translation.x, &rotationDecompose.x, &scaledDecompose.x);
                    translation -= position;

                    selected->mPhysicObject->Move(translation);
                    selected->mPhysicObject->SetRotation(rotation);
                    selected->mPhysicObject->SetScale(scaledDecompose);
                }
            }

            // glm::mat4 transformMatrix = selected->transform.GetModelMatrix();
            // ImGuizmo::Manipulate(glm::value_ptr(EditorCamera::Instance().GetView()), glm::value_ptr(EditorCamera::Instance().GetProjection()),
            //     (ImGuizmo::OPERATION)mOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(transformMatrix));
            
            // if (ImGuizmo::IsUsing())
            // {
            //     selected->transform.SetTransform(transformMatrix);
            //     if (selected->mPhysicObject)
            //     {
            //         selected->mPhysicObject->SetTransformMatrix(transformMatrix);
            //     }
            // }



            // if (selected->mPhysicObject)
            // {
            //     glm::mat4 transformMatrix = selected->mPhysicObject->GetTransform();
            //     ImGuizmo::Manipulate(glm::value_ptr(EditorCamera::Instance().GetView()), glm::value_ptr(EditorCamera::Instance().GetProjection()), 
            //         (ImGuizmo::OPERATION)mOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(transformMatrix));

            //     /* If we moved the manipulator */
            //     if (ImGuizmo::IsUsing())
            //     {
            //         glm::vec3 decomposePosition, decomposeRotation, decomposeScale;
            //         ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transformMatrix), &decomposePosition.x, &decomposeRotation.x, &decomposeScale.x);
            //         switch (mOperation)
            //         {
            //         case GizmoOperation::TRANSLATE:
            //         {
            //             selected->mPhysicObject->SetPosition(decomposePosition);                
            //         }
            //         break;
            //         case GizmoOperation::ROTATE:
            //             selected->mPhysicObject->SetRotation(glm::quat(glm::radians(decomposeRotation)));
            //             break;
            //         case GizmoOperation::SCALE:
            //             selected->mPhysicObject->SetScale(decomposeScale);
            //             break;
            //         default:
            //             break;
            //         }
            //     }                    
            // }
            // else 
            // {
            //     glm::mat4 transformMatrix = selected->transform.GetModelMatrix();
            //     ImGuizmo::Manipulate(glm::value_ptr(EditorCamera::Instance().GetView()), glm::value_ptr(EditorCamera::Instance().GetProjection()), 
            //         (ImGuizmo::OPERATION)mOperation, ImGuizmo::MODE::LOCAL, glm::value_ptr(transformMatrix));   

            //     if (ImGuizmo::IsUsing())
            //     {
            //         transformMatrix *= glm::inverse(selected->transform.GetModelMatrix());
            //         selected->transform.SetTransform(transformMatrix);                    
            //     }             
            // }
        }
    }
}