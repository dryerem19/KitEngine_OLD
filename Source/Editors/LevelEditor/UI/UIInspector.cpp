#include "UIInspector.h"

#include "Entity.h"

namespace LevelEditor
{
    //----------------------------------------------------------------------------------------
    // PUBLIC    
    //----------------------------------------------------------------------------------------

    void Inspector::Draw()
    {
        ImGui::Begin("Object inspector");
        {
            DrawTransformComponent();
        }
        ImGui::End();
    }

    void Inspector::DrawMaterial()
    {

    }

    //----------------------------------------------------------------------------------------
    // PRIVATE 
    //----------------------------------------------------------------------------------------

    void Inspector::DrawTransformComponent()
    {
        auto selected = Render::GameLevel::Get().GetSelectedEntity();
        if (!selected)
        {
            return;
        }
        auto& tr = selected->GetTransform();

        float position_x = tr.GetPosition().x;
        float position_y = tr.GetPosition().y;
        float position_z = tr.GetPosition().z;

        float rotation_x = glm::degrees(tr.GetRotation().x);
        float rotation_y = glm::degrees(tr.GetRotation().y);
        float rotation_z = glm::degrees(tr.GetRotation().z);

        float scale_x = tr.GetScale().x;
        float scale_y = tr.GetScale().y;
        float scale_z = tr.GetScale().z;

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 0.0f));

        ImGui::Text("Position");
        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.8f, 0.1f, 0.15f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f)); 
        if (ImGui::Button("X ## 1")) { position_x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 1", &position_x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 1")) { position_y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 1", &position_y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 1")) { position_z = 0.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 1", &position_z, 0.1f);
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
        if (ImGui::Button("X ## 2")) { rotation_x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 2", &rotation_x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 2")) { rotation_y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 2", &rotation_y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 2")) { rotation_z = 0.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 2", &rotation_z, 0.1f);
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
        if (ImGui::Button("X ## 3")) { scale_x = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##x ## 3", &scale_x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.2f, 0.7f, 0.2f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
        if (ImGui::Button("Y ## 3")) { scale_y = 0.0f; }
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();
            ImGui::DragFloat("##y ## 3", &scale_y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.25f, 0.8f, 1.0f)); 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f)); 
        if (ImGui::Button("Z ## 3")) { scale_z = 1.0f; }   
        ImGui::PopStyleColor(3);
        {
            ImGui::SameLine();                 
            ImGui::DragFloat("##z ## 3", &scale_z, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
        }        

        ImGui::PopStyleVar();

        tr.SetPosition(glm::vec3(position_x, position_y, position_z));
        tr.SetRotation(glm::radians(glm::vec3(rotation_x, rotation_y, rotation_z)));
        tr.SetScale(glm::vec3(scale_x, scale_y, scale_z));
    } 
}