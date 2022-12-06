/**
 * @file UIContentBrowser.h
 * @author EvgehaName (dubasov.eugeni@yandex.ru)
 * @brief UI element Content Browser
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Core/KitUI.h"
#include <filesystem>
#include <fstream>

namespace LevelEditor
{
    class UIContentBrowser : public KitUI
    {
    public:
        UIContentBrowser();
        void Draw() override;
        void NewFile( bool* close, bool isFolder = false );
        void DeleteFile( bool* close );
        void RenameFile( bool* close );

    private:
        const std::filesystem::path mProjectDirectory = "data";
        std::filesystem::path mCurrentProjectDirectory;
        std::filesystem::path mLastDirectory = "data";
        ImGuiItemFlags mFlagsButtonBack = 0;
        ImGuiItemFlags mFlagsButtonForward = 0;
        std::string mNameFile = "";
        std::string mNewNameFile = "";
        std::string mOldNameFileRename;
        std::string mNameFileDelete;

        bool mIsCheckNewFile = false;
        bool mIsFolder = false;
        bool mIsCheckDeleteFile = false;
        bool mIsCheckRenameFile = false;
    };
}