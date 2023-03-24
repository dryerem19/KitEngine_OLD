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
#include "KitModelFile.h"
#include "../Core/KitUI.h"

#include "Scene.h"

namespace fs = std::filesystem;

class ModelImportTool final
{
private:
    /* Директория сохранения материалов */
    fs::path mMaterialSaveDirectory;

    /* Директория сохранения текстур */
    fs::path mTextureSaveDirectory;
public:
    /* Путь до модели, которую нужно импортировать */
    fs::path mModelFilepath;

    /* Директория, откуда копируем текстуры */
    fs::path mTextureDirectory;

    /* Директория сохранения */
    fs::path mSaveDirectory;

    /* Список сообщений импорта */
    std::stringstream mLogList;

    /* Импортированная модель */
    KitModelFile mKmfFile;

    explicit ModelImportTool() = default;
    bool Import();
    
    
    
    bool Load(const std::string& filepath, Scene* pScene);



    void Save();
private:
    void CreateDirectory(const fs::path& path);
    void ParseMeshes(const aiScene* pScene);
    std::string ProcessAssimpMaterial(const aiMaterial* pMaterial);
};