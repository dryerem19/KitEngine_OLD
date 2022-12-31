#include "UISaveClose.h"

namespace LevelEditor
{
    void UISaveClose::Draw()
    {
        ImGui::SetWindowSize(ImVec2(300.0f, 150.0f));
        ImGui::Begin("Saving the project", &mIsCheckClose, ImGuiWindowFlags_NoDocking);
        {
            ImGui::Text("You have not saved the project, do you want to save it before closing?");
            if(ImGui::Button("Yes"))
            {
                Core::Application::Instance().Close();
            }
            ImGui::SameLine();
            if(ImGui::Button("No"))
            {
                Core::Application::Instance().Close();
            }
            ImGui::SameLine();
            if(ImGui::Button("Cancel"))
            {
                mIsCheckClose = false;
            }
            // if(mIsCheckClose == false)
            // {
            //     Core::Application::Instance().Close();
            // }
        }
        ImGui::End();
    }

}
