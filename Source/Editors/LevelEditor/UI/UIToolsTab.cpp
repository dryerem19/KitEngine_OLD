#include "UIToolsTab.h"

namespace LevelEditor
{
    void ToolsTab::Draw()
    {
        ImGui::Begin("ToolsTab");
        ImGui::BeginTabBar("ToolsTab##TabBar");
        {
            if (ImGui::BeginTabItem("Lights"))
            {
                this->DrawLightsTab();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
        ImGui::End();
    }

    void ToolsTab::DrawLightsTab()
    {
        static Render::LightType selectedType = Render::LightType::None;

        if (ImGui::TreeNode("Base"))
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
            if (ImGui::TreeNodeEx(ICON_FA_SUN "\t" "Directional Light", flags | 
                        (selectedType == Render::LightType::DirectionalLight 
                            ? ImGuiTreeNodeFlags_Selected : 0)))
            {
                if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                {
                    selectedType = Render::LightType::DirectionalLight;
                }                
                ImGui::TreePop();
            }
            if (ImGui::TreeNodeEx(ICON_FA_LIGHTBULB "\t" "Point Light", flags |
                    (selectedType == Render::LightType::PointLight ? 
                        ImGuiTreeNodeFlags_Selected : 0)))
            {
                if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                {
                    selectedType = Render::LightType::PointLight;
                }
                ImGui::TreePop();
            }            
            if (ImGui::TreeNodeEx(ICON_FA_LIGHTBULB "\t" "Spot Light", flags |
                    (selectedType == Render::LightType::SpotLight ?
                         ImGuiTreeNodeFlags_Selected : 0)))
            {
                if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                {
                    selectedType = Render::LightType::SpotLight;
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        if (ImGui::Button("Add", ImVec2(ImGui::GetWindowWidth(), 25)));
        {

        }        
    }
} 
