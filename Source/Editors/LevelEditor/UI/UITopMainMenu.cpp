#include "UITopMainMenu.h"

#include "Model.h"

namespace LevelEditor
{
    void UITopMainMenu::Draw()
    {
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu(ICON_FA_FILE " File"))
            {
                if(ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Scene")){
                    GameLevel::Get().Deserialize("test.level");
                }
                if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Scene"))
                {
                    GameLevel::Get().Serialize("test");
                }
                if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Scene As..")){
                
                }
                ImGui::Separator();
                if(ImGui::MenuItem(ICON_FA_SQUARE_PLUS " New Project")){

                }
                if(ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Project")){
                    
                }
                if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Project")){

                }
                ImGui::Separator();
                if(ImGui::MenuItem(ICON_FA_RIGHT_FROM_BRACKET " Exit"))
                {
                    Core::Application::Instance().Close();
                }
                ImGui::EndMenu();
            }
            static bool open = false;
            {
                if(open)
                    ShowAbout(&open);
                if(ImGui::MenuItem(ICON_FA_ADDRESS_CARD " About"))
                    open = true;
            }

        }
        ImGui::EndMainMenuBar();
    }

    void UITopMainMenu::ShowAbout(bool* close)
    {
        if(close)
        {
            ImGui::SetNextWindowSize(ImVec2(250,250));
            ImGui::Begin("About", close, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
            ImGui::Text("Name Product: KitEngine");
            ImGui::Text("Develepers: dryerem19, EvgehaName");
            ImGui::End();
        }
    }
}