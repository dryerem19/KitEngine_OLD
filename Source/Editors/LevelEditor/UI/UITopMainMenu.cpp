#include "UITopMainMenu.h"

namespace UI
{
    void UITopMainMenu::Draw()
    {
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu(ICON_FA_FILE " File"))
            {
                if(ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Scene")){

                }
                if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save Scene")){

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
                if(ImGui::BeginMenu("Import Model"))
                {
                    if(ImGui::MenuItem("Нано-костюм")){
                        std::string filepath = "../../Resources/models/nanosuit/nanosuit.obj";
                        OnLoadModel(&filepath);
                    }
                    ImGui::Separator();
                    if(ImGui::MenuItem(ICON_FA_FILE_IMPORT " Open Model"))
                    {
                        isCheckFileDialog = true;
                    }
                                    
                    ImGui::EndMenu();
                }
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

        if(isCheckFileDialog){
            std::string filepath = UIFileDialog::OpenFile(".*, .fbx, .obj, .stl", &isCheckFileDialog);
            if(!filepath.empty()){
                OnLoadModel(&filepath);
            }
        }
    }

    void UITopMainMenu::OnLoadModel(std::string* filepath)
    {
        uiSceneTree->mNanoModel.Init(*filepath);
        uiSceneTree->isModelLoaded = true;
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