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

    }

    void UIContentBrowser::Draw()
    {
        ImGui::Begin("Content Browser");
        {
            if(ImGui::ButtonEx("<-", ImVec2(0.0f, 0.0f), mFlagsButtonBack))
            {
                if(mCurrentProjectDirectory != mProjectDirectory)
                {
                    mLastDirectory = mCurrentProjectDirectory;
                }
                mCurrentProjectDirectory = mCurrentProjectDirectory.parent_path();
            }
            ImGui::SameLine();
            if(ImGui::ButtonEx("->", ImVec2(0.0f, 0.0f), mFlagsButtonForward))
            {
                mCurrentProjectDirectory = mLastDirectory;
            }
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
            ImGui::Separator();
            
            for(auto&& path : std::filesystem::directory_iterator(mCurrentProjectDirectory))
            {
                auto relative = std::filesystem::relative(path.path(), mProjectDirectory);
                
                if(path.is_directory())
                {
                    if(ImGui::Button(relative.filename().c_str()))
                    {
                        mCurrentProjectDirectory /= relative.filename();
                        mLastDirectory = mCurrentProjectDirectory;
                    }
                }
                else
                {
                    if(ImGui::Button(relative.filename().c_str()))
                    {

                    }
                }
                if(ImGui::BeginPopupContextItem(relative.filename().c_str()))
                {
                    if(ImGui::Selectable("Delete"))
                    {
                        mNameFileDelete = relative.filename();
                        mIsCheckDeleteFile = true;
                    }
                    ImGui::Separator();
                    if(ImGui::Selectable("Rename"))
                    {
                        mOldNameFileRename = relative.filename();
                        mIsCheckRenameFile = true;
                    }
                    ImGui::EndPopup();
                }
            }
            
            if(std::filesystem::is_empty(mCurrentProjectDirectory))
            {
                ImGui::Text("No Item");
            }

            if(mCurrentProjectDirectory != mProjectDirectory)
            {
                mFlagsButtonBack = 0;
            }
            else
            {
                mFlagsButtonBack = ImGuiItemFlags_Disabled;
            }
            
            if(mCurrentProjectDirectory != mLastDirectory)
            {
                mFlagsButtonForward = 0;
            }
            else
            {
                mFlagsButtonForward = ImGuiItemFlags_Disabled;
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