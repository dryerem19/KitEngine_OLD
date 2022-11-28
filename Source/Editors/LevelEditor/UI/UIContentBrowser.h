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

namespace LevelEditor
{
    class UIContentBrowser : public KitUI
    {
    public:
        UIContentBrowser();
        void Draw() override;

        const std::filesystem::path mProjectDirectory = "project";
        std::filesystem::path mLastDirectory = "project";
        ImGuiItemFlags flagsButtonBack = 0;
        ImGuiItemFlags flagsButtonForward = 0;

        

    private:
        std::filesystem::path mCurrentProjectDirectory;
    };
}