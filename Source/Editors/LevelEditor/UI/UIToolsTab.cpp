#include "UIToolsTab.h"

namespace LevelEditor
{
    void ToolsTab::Draw()
    {
        auto& level = GameLevel::Get();

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


        if (ImGui::Button("Add sound")) {
            auto* pSound = level.CreateSound();
            pSound->Init("../../Resources/sound/test.mp3");
            pSound->Play();
        }

        ImGui::End();
    }

    void ToolsTab::DrawLightsTab()
    {
        // static LightType selectedType = LightType::None;

        // if (ImGui::TreeNode("Base"))
        // {
        //     ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;
        //     if (ImGui::TreeNodeEx(ICON_FA_SUN "\t" "Directional Light", flags | 
        //                 (selectedType == LightType::DirectionalLight 
        //                     ? ImGuiTreeNodeFlags_Selected : 0)))
        //     {
        //         if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        //         {
        //             selectedType = LightType::DirectionalLight;
        //         }                
        //         ImGui::TreePop();
        //     }
        //     if (ImGui::TreeNodeEx(ICON_FA_LIGHTBULB "\t" "Point Light", flags |
        //             (selectedType == LightType::PointLight ? 
        //                 ImGuiTreeNodeFlags_Selected : 0)))
        //     {
        //         if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        //         {
        //             selectedType = LightType::PointLight;
        //         }
        //         ImGui::TreePop();
        //     }            
        //     if (ImGui::TreeNodeEx(ICON_FA_LIGHTBULB "\t" "Spot Light", flags |
        //             (selectedType == LightType::SpotLight ?
        //                  ImGuiTreeNodeFlags_Selected : 0)))
        //     {
        //         if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        //         {
        //             selectedType = LightType::SpotLight;
        //         }
        //         ImGui::TreePop();
        //     }
        //     ImGui::TreePop();
        // }



        if (ImGui::Button("Add", ImVec2(ImGui::GetWindowWidth(), 25)))
        {
            GameLevel::Get().CreateLigth();
        }
        if(!GameLevel::Get()._lights.empty())
        {
            ImGui::ColorPicker4("Picker", &GameLevel::Get()._lights[0]->mColor.x);
            ImGui::DragFloat("Intensity\nAmbient", &GameLevel::Get()._lights[0]->mAmbientStrength, 0.01f, 0.0f, 50.0f);
            ImGui::DragFloat("Intensity\nSpecular", &GameLevel::Get()._lights[0]->mSpecularStrength, 0.01f, 0.0f, 10.0f);
        }

    }
} 
