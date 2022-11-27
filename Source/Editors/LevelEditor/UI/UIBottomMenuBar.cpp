#include "UIBottomMenuBar.h"

namespace LevelEditor
{
    void BottomMenuBar::Draw()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 20));
        ImGui::SetNextWindowPos(ImVec2(0.0f, io.DisplaySize.y - 20.0f));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking       | 
                                        ImGuiWindowFlags_NoTitleBar      | 
                                        ImGuiWindowFlags_NoResize        | 
                                        ImGuiWindowFlags_NoMove          | 
                                        ImGuiWindowFlags_NoScrollbar     | 
                                        ImGuiWindowFlags_NoSavedSettings | 
                                        ImGuiWindowFlags_MenuBar;
        ImGui::Begin("BottomMenuBar", 0, window_flags);
        {
            ImGui::BeginMenuBar();
            {
                ImGuiIO& io = ImGui::GetIO();
                const auto& camera_pos = EditorCamera::Instance().GetPos();
                ImGui::Text("Cam: [ x: %.3f, y: %.3f, z: %.3f ]", camera_pos.x, camera_pos.y, camera_pos.z);
                ImGui::Separator();
                ImGui::Text("Cur: [ x: %d, y: %d ]", (uint32_t)io.MousePos.x, (uint32_t)io.MousePos.y);
            }
            ImGui::EndMenuBar();   
        }
        ImGui::End();
    }
}