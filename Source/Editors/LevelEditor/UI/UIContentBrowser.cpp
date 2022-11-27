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
            if(ImGui::ButtonEx("<-", ImVec2(0.0f, 0.0f), flagsButtonBack))
            {
                if(mCurrentProjectDirectory != mProjectDirectory)
                {
                    mLastDirectory = mCurrentProjectDirectory;
                }
                mCurrentProjectDirectory = mCurrentProjectDirectory.parent_path();
                std::cout << mCurrentProjectDirectory << std::endl;
            }
            ImGui::SameLine();
            if(ImGui::ButtonEx("->", ImVec2(0.0f, 0.0f), flagsButtonForward))
            {
                mCurrentProjectDirectory = mLastDirectory;
                std::cout << mCurrentProjectDirectory << std::endl;
            }
            ImGui::Separator();
            
            for(auto&& path : std::filesystem::directory_iterator(mCurrentProjectDirectory))
            {
                auto relative = std::filesystem::relative(path.path(), mProjectDirectory);
                if(path.is_directory())
                {
                    
                    if(ImGui::Button(relative.string().c_str()))
                    {
                        mCurrentProjectDirectory /= relative.filename();
                        mLastDirectory = mCurrentProjectDirectory;
                        std::cout << "|| C " <<mCurrentProjectDirectory << " || L " << mLastDirectory  << std::endl;
                    }
                    if(mCurrentProjectDirectory != mProjectDirectory)
                    {
                        flagsButtonBack = 0;
                    }
                    else
                    {
                       flagsButtonBack = ImGuiItemFlags_Disabled;
                    }
                    // TODO: Нужно исправить возвращение на последнюю папку [->]
                    if(mCurrentProjectDirectory != mLastDirectory)
                    {
                        flagsButtonForward = 0;
                    }
                    else
                    {
                        flagsButtonForward = ImGuiItemFlags_Disabled;
                    }
                }
                else
                {
                    if(ImGui::Button(relative.string().c_str()))
                    {

                    }
                }
            }
        }
        ImGui::End();
    }
}