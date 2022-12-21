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
#include "MeshVisualImporter.h"

#include "Tools/ModelImportTool.h"

#include "ResourceManager.h"
#include "GameLevel.h"

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
        std::string mNameFile = "";
        std::string mNewNameFile = "";
        std::string mOldNameFileRename;
        std::string mNameFileDelete;
        float mIconsSize = 100.0f;
        float mPaddingFiles = 5.0f;
        ImFont* fontIcons = nullptr;
        std::filesystem::path _currentDirectory;
        std::vector<std::filesystem::path> _forwardDirectory;
        

        int _currentDirectoryId;

        bool mIsCheckNewFile = false;
        bool mIsFolder = false;
        bool mIsCheckDeleteFile = false;
        bool mIsCheckRenameFile = false;

        bool mImportWindowOpen;
        bool mMeshImportModel;
        std::string mModelValidExtensionList;
        std::filesystem::path mImportFilePath;
        std::string mModelImportTextureDirectory;
    };
}