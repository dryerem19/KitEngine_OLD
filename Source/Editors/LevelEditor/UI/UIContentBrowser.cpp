/**
 * @file UIContentBrowser.cpp
 * @author EvgehaName (dubasov.eugeni@yandex.ru)
 * @brief UI element Content Browser
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "UIContentBrowser.h"
namespace LevelEditor
{
    UIContentBrowser::UIContentBrowser() : mCurrentProjectDirectory(mProjectDirectory)
    {
        _currentDirectory = "data";
        _forwardDirectory.push_back(_currentDirectory);
        _currentDirectoryId = 0;
    }

    void UIContentBrowser::Draw()
    {
        ImGui::Begin("Content Browser");
        {
            if(ImGui::Button(ICON_FA_ARROW_LEFT, ImVec2(0.0f, 0.0f))) {
                if(!(_currentDirectory == _forwardDirectory[0]))
                    _currentDirectoryId--;
                if(_currentDirectoryId < 0)
                    _currentDirectoryId = 0;
                if (_currentDirectory.has_parent_path())
                    _currentDirectory = _currentDirectory.parent_path();
                std::cout << "back: " << _currentDirectoryId << "\n";
                std::cout << "folder: " << _currentDirectory << "\n";
            }

            ImGui::SameLine();
            if(ImGui::Button(ICON_FA_ARROW_RIGHT, ImVec2(0.0f, 0.0f))) {
                _currentDirectoryId++;
                if (_currentDirectoryId >= _forwardDirectory.size())
                    _currentDirectoryId = _forwardDirectory.size() - 1;
                
                _currentDirectory = _forwardDirectory[_currentDirectoryId];
                std::cout << "forward: " << _currentDirectoryId << "\n";
                std::cout << "folder: " << _currentDirectory << "\n";
            }
            ImGui::SameLine();
            ImGui::Text(_currentDirectory.filename().string().c_str());

            

            if(ImGui::BeginPopupContextWindow("Content Browser"))
            {
                if(ImGui::Selectable("New Folder"))
                {
                    mIsCheckNewFile = true;
                    mIsFolder = false;
                }
                ImGui::Separator();
                if(ImGui::Selectable("New File"))
                {
                    mIsCheckNewFile = true;
                    mIsFolder = true;
                }
                ImGui::EndPopup();
            }
            float size = mIconsSize + mPaddingFiles;
            float panelWidth = ImGui::GetContentRegionAvail().x;
            int countCol = (int)(panelWidth / size);
            ImGui::Separator();
            if(countCol >= 1)
                ImGui::Columns(countCol, 0, false);
            
            static ImVec4 btn_primary_color = ImVec4(0.f, 0.f, 0.f, 0.f);
            static ImVec4 btn_hovered_color = ImVec4(0.f, 0.f, 0.f, 0.f);
            static ImVec4 btn_actived_color = ImVec4(0.f, 0.f, 0.f, 0.f);
            
            static std::string selected_filepath; 
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                selected_filepath.clear();
  
            for(auto&& path : std::filesystem::directory_iterator(_currentDirectory))
            {
                auto relative = std::filesystem::relative(path.path(), mProjectDirectory);
                auto filename = relative.filename().string();
                auto filepath = relative.string();
                
                bool selected = selected_filepath == relative.string();
                btn_primary_color = selected ? ImVec4(0.2f, 0.2f, 0.2f, 1.f) : ImVec4(0.f, 0.f, 0.f, 0.f);
                btn_hovered_color = selected ? btn_primary_color : ImVec4(0.15f, 0.15f, 0.15f, 1);
                btn_actived_color = btn_hovered_color;
                                
                ImGui::PushStyleColor(ImGuiCol_Button, btn_primary_color);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, btn_hovered_color);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, btn_actived_color);

                const char* icon = path.is_directory() ? ICON_FA_FOLDER_OPEN : ICON_FA_FILE; 
                ImGui::PushFont(g_pFontContentBrowser);
                ImGui::Button(icon, ImVec2(mIconsSize, mIconsSize));
                ImGui::PopFont();
                ImGui::PopStyleColor(3);

                if (ImGui::IsItemHovered()) {
                    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && 
                        !ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                        selected_filepath = filepath;
                    }

                    else if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)
                        && path.is_directory()) 
                    {
                        _currentDirectory.append(filename);
                        if(_forwardDirectory.back() != _currentDirectory) 
                        {
                            _forwardDirectory.push_back(_currentDirectory);
                            _currentDirectoryId = _forwardDirectory.size() - 1;
                        }
                    }                    
                }

                if(ImGui::BeginPopupContextItem(filename.c_str()))
                {
                    if(ImGui::Selectable("Delete"))
                    {
                        mNameFileDelete = filename;
                        mIsCheckDeleteFile = true;
                    }
                    ImGui::Separator();
                    if(ImGui::Selectable("Rename"))
                    {
                        mOldNameFileRename = filename;
                        mIsCheckRenameFile = true;
                    }
                    ImGui::EndPopup();
                }

                ImGui::Text(filename.c_str());

                ImGui::NextColumn();
                // if(ImGui::BeginDragDropSource())
                // {
                //     std::string item = relative.filename().string();
                //     ImGui::SetDragDropPayload("Item_content_browser", (wchar_t*)item.c_str(), wcslen((wchar_t*)item.c_str()) * sizeof(wchar_t));
                //     ImGui::EndDragDropSource();
                // }

            }
            ImGui::Columns(1);
            
            if(std::filesystem::is_empty(_currentDirectory))
            {
                ImGui::Text("No Item");
            }
        }
        ImGui::End();

        if(mIsCheckNewFile)
        {
            NewFile(&mIsCheckNewFile, mIsFolder);
        }
        if(mIsCheckDeleteFile)
        {
            DeleteFile(&mIsCheckDeleteFile);
        }
        if(mIsCheckRenameFile)
        {
            RenameFile(&mIsCheckRenameFile);
        }
    }

    void UIContentBrowser::NewFile( bool* close, bool isFolder /*= false*/ )
    {
        const char* title = isFolder == false ? "Create Folder" : "Create File";
        const char* nameInput = isFolder == false ? "Name Folder" : "Name File";
        ImGui::SetNextWindowSize(ImVec2(300.0f,100.0f));
        ImGui::Begin(title, close, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
        {
            ImGui::InputText(nameInput, &mNameFile);
            if(ImGui::Button("Add"))
            {
                if(!isFolder)
                {
                    std::filesystem::create_directories(mCurrentProjectDirectory / mNameFile);
                    mIsCheckNewFile = false;
                    mNameFile.clear();
                }
                else
                {
                    std::ofstream fstream(mCurrentProjectDirectory / mNameFile);
                    fstream.close();
                    mNameFile.clear();
                    mIsCheckNewFile = false;
                }
            }
            ImGui::SameLine();
            if(ImGui::Button("Close"))
            {
                mIsCheckNewFile = false;
            }
        }
        ImGui::End();
    }

    void UIContentBrowser::DeleteFile(bool* close)
    {
        ImGui::Begin("Delete File", close, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
        {
            ImGui::Text("Would you like to delete a file ?");
            if(ImGui::Button("Yes"))
            {
                std::filesystem::remove_all(mCurrentProjectDirectory / mNameFileDelete);
                mNameFileDelete.clear();
                mIsCheckDeleteFile = false;
            }
            ImGui::SameLine();
            if(ImGui::Button("No"))
            {
                mIsCheckDeleteFile = false;
            }
        }
        ImGui::End();
    }

    void UIContentBrowser::RenameFile(bool* close)
    {
        const char* nameInput = "New Name File";
        ImGui::SetNextWindowSize(ImVec2(300.0f,100.0f));
        ImGui::Begin("Rename File", close, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
        {
            ImGui::InputText(nameInput, &mNewNameFile);
            if(ImGui::Button("Rename"))
            {
                std::filesystem::rename(mCurrentProjectDirectory / mOldNameFileRename, mCurrentProjectDirectory / mNewNameFile);
                mNewNameFile.clear();
                mOldNameFileRename.clear();
                mIsCheckRenameFile = false;
            }
            ImGui::SameLine();
            if(ImGui::Button("Cancel"))
            {
                mIsCheckRenameFile = false;
            }
        }
        ImGui::End();
    }
}