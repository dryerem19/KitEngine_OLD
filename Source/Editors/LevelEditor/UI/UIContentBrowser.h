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
#include <stack>

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
        float mIconsSize = 100.0f;
        float mPaddingFiles = 5.0f;
        ImFont* fontIcons = nullptr;

        std::vector<std::filesystem::path> _historyDirectory;
        std::string _projectDirectory;


        std::filesystem::path _startDirectory;
        std::filesystem::path _currentDirectory;
        std::filesystem::path _endDirectory;

        std::filesystem::path _lastDirectory;

        std::vector<std::filesystem::path> _forwardDirectory;
        

        int _currentDirectoryId;

        bool mIsCheckNewFile = false;
        bool mIsFolder = false;
        bool mIsCheckDeleteFile = false;
        bool mIsCheckRenameFile = false;
    };
}