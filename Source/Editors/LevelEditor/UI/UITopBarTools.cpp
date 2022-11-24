#include "UITopBarTools.h"

namespace LevelEditor
{
    void UITopBarTools::Draw()
    {
        if(ImGui::BeginMenuBar())
        {   
            static bool selected_arrow_left   = false;
            static bool selected_arrow_right  = false;
            static bool selected_gizmo_rotate = false;
            static bool selected_gizmo_scale  = false;
            static bool selected_gizmo_move   = false;
            static bool selected_pointer      = false;

            // Arrow left - undo (назад)
            if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_LEFT, nullptr, &selected_arrow_left))
            {
                selected_arrow_left   = true;   
                selected_arrow_right  = false;
                selected_pointer      = false;
                selected_gizmo_move   = false;
                selected_gizmo_rotate = false;
                selected_gizmo_scale  = false;                    
            }
            
            // Arrow right - redo (вперед)
            if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_RIGHT, nullptr, &selected_arrow_right))
            {
                selected_arrow_right  = true;
                selected_pointer      = false;
                selected_arrow_left   = false;
                selected_gizmo_move   = false;
                selected_gizmo_rotate = false;
                selected_gizmo_scale  = false;                   
            }

            // Enable mouse pointer
            if(ImGui::MenuItem(ICON_FA_ARROW_POINTER, nullptr, &selected_pointer))
            {

                SelectGizmoEvent e(GizmoOperation::NONE);
                mController->OnNotify(this, e);

                selected_pointer      = true;
                selected_arrow_left   = false;
                selected_arrow_right  = false;
                selected_gizmo_move   = false;
                selected_gizmo_rotate = false;
                selected_gizmo_scale  = false;                

            }

            // Enable movement object (gizmo)
            if(ImGui::MenuItem(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT, nullptr, &selected_gizmo_move))
            {
                selected_gizmo_move   = true;
                selected_arrow_left   = false;
                selected_arrow_right  = false;
                selected_gizmo_rotate = false;
                selected_gizmo_scale  = false;
                selected_pointer      = false;

                SelectGizmoEvent e(GizmoOperation::TRANSLATE);
                mController->OnNotify(this, e);
            }

            // Enable rotate object (gizmo)
            if(ImGui::MenuItem(ICON_FA_ROTATE, nullptr, &selected_gizmo_rotate))
            {
                selected_gizmo_rotate = true;
                selected_arrow_left   = false;
                selected_arrow_right  = false;
                selected_gizmo_move   = false;
                selected_gizmo_scale  = false;
                selected_pointer      = false;                

                SelectGizmoEvent e(GizmoOperation::ROTATE);
                mController->OnNotify(this, e);
            }

            // Enable scale object (gizmo)
            if(ImGui::MenuItem(ICON_FA_UP_RIGHT_FROM_SQUARE, nullptr, &selected_gizmo_scale))
            {
                selected_gizmo_scale  = true;
                selected_arrow_left   = false;
                selected_arrow_right  = false;
                selected_gizmo_rotate = false;
                selected_gizmo_move   = false;
                selected_pointer      = false;

                SelectGizmoEvent e(GizmoOperation::SCALE);
                mController->OnNotify(this, e);
            }

            ImGui::Separator();
            if(ImGui::BeginMenu(ICON_FA_DRAW_POLYGON))
            {
                if(ImGui::MenuItem(ICON_FA_CIRCLE " Vertices"))
                {
                    Render::Renderer::Wireframe(Render::WireframeMode::Vertices);
                }
                if(ImGui::MenuItem(ICON_FA_SLASH " Edge"))
                {
                    Render::Renderer::Wireframe(Render::WireframeMode::Edge);
                }
                if(ImGui::MenuItem(ICON_FA_SQUARE " Polygon"))
                {
                    Render::Renderer::Wireframe(Render::WireframeMode::Polygon);
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if(ImGui::BeginMenu("Camera Speed"))
            {
                if(ImGui::MenuItem("x1"))
                {
                    EditorCamera::Instance().cameraSpeed = 0.30f;
                }
                if(ImGui::MenuItem("x2"))
                {
                    EditorCamera::Instance().cameraSpeed = 0.60f;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
}