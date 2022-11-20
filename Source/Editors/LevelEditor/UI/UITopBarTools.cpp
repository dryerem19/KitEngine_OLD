#include "UITopBarTools.h"

namespace UI
{
    void UITopBarTools::Draw()
    {
        if(ImGui::BeginMenuBar())
        {   
            // Arrow left - undo (назад)
            if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_LEFT))
            {
                
            }
            // Arrow right - redo (вперед)
            if(ImGui::MenuItem(ICON_FA_CIRCLE_ARROW_RIGHT))
            {

            }
            // Enable mouse pointer
            if(ImGui::MenuItem(ICON_FA_ARROW_POINTER))
            {

            }
            // Enable movement object (gizmo)
            if(ImGui::MenuItem(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT))
            {
                mode = ImGuizmo::OPERATION::TRANSLATE;
            }
            // Enable rotate object (gizmo)
            if(ImGui::MenuItem(ICON_FA_ROTATE))
            {
                mode = ImGuizmo::OPERATION::ROTATE;
            }
            // Enable scale object (gizmo)
            if(ImGui::MenuItem(ICON_FA_UP_RIGHT_FROM_SQUARE))
            {
                mode = ImGuizmo::OPERATION::SCALE;
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
            ImGui::EndMenuBar();
        }
    }
}