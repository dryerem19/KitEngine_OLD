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

    private:
        const std::filesystem::path mProjectDirectory = "project";
        std::filesystem::path mCurrentProjectDirectory;
        std::filesystem::path mLastDirectory = "project";
        ImGuiItemFlags mFlagsButtonBack = 0;
        ImGuiItemFlags mFlagsButtonForward = 0;
        std::string mNameFile = "";

        bool mIsCheckOnNewFolder = false;
        bool mIsFolder = false;
    };
}