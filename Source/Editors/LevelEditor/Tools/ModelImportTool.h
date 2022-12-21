/**
 * @file ModelImportTool.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <filesystem>
#include "../Core/KitUI.h"

class ModelImportTool final
{
public:
    std::filesystem::path mModelFilepath;
    std::filesystem::path mTextureDirectory;
    std::filesystem::path mSaveDirectory;
    std::stringstream mLogList;

    explicit ModelImportTool() = default;
    bool Import();
private:
    void CreateDirectory(const std::filesystem::path& path);
};