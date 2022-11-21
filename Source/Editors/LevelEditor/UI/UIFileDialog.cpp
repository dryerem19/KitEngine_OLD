#include "UIFileDialog.h"

namespace LevelEditor
{
    std::string UIFileDialog::OpenFile(const std::string& filters,bool* isCheckFileDialog)
    {
        std::string filepath;
        
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", filters.c_str(), ".");
        ImGui::SetNextWindowSizeConstraints(ImVec2(600,400), ImVec2(-1,-1));
        
        if(ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if(ImGuiFileDialog::Instance()->IsOk())
            {
                filepath = ImGuiFileDialog::Instance()->GetFilePathName();
            }
            ImGuiFileDialog::Instance()->Close();
            *isCheckFileDialog = false;
        }

        return filepath;
    }
}