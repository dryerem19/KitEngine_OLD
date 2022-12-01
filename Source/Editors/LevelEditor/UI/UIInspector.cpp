#include "UIInspector.h"

namespace LevelEditor
{
    //----------------------------------------------------------------------------------------
    // PUBLIC    
    //----------------------------------------------------------------------------------------

    void Inspector::Draw()
    {
        ImGui::Begin("Object inspector");
        {
            // auto& scene_manager = Render::SceneManager::Instance();
            // auto selected_object = scene_manager.GetSelectedObject();
            // if (selected_object)
            // {
            //     auto& tag = selected_object.GetComponent<Render::KitTag>();
            //     ImGui::Text("Name: %s", tag.Tag.c_str());

            //     auto& transform = selected_object.GetComponent<Render::KitTransform>();
            //     if (ImGui::CollapsingHeader("Transform"))
            //     {
            //         this->DrawTransformComponent(transform);
            //     }
            // }
        }
        ImGui::End();
    }

    //----------------------------------------------------------------------------------------
    // PRIVATE 
    //----------------------------------------------------------------------------------------

    void Inspector::DrawTransformComponent(Render::KitTransform& transform)
    {
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 0.0f));

        ImGui::Text("Position");
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f)); 
        if (ImGui::Button("X ## 1")) { transform.Translation.x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 1", &transform.Translation.x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 1")) { transform.Translation.y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 1", &transform.Translation.y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 1")) { transform.Translation.z = 0.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 1", &transform.Translation.z, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::Text("Rotation");
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f)); 
        if (ImGui::Button("X ## 2")) { transform.Rotation.x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 2", &transform.Rotation.x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 2")) { transform.Rotation.y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 2", &transform.Rotation.y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 2")) { transform.Rotation.z = 0.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 2", &transform.Rotation.z, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::Text("Scale");
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f)); 
        if (ImGui::Button("X ## 3")) { transform.Scale.x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 3", &transform.Scale.x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 3")) { transform.Scale.y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 3", &transform.Scale.y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 3")) { transform.Scale.z = 0.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 3", &transform.Scale.z, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }        

        ImGui::PopStyleVar();
    } 
}