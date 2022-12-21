/**
 * @file ModelImportTool.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ModelImportTool.h"

bool ModelImportTool::Import()
{
    if (!std::filesystem::exists(mModelFilepath)) {
        mLogList << "[ERROR] - File not found";
        return false;
    }

    if (!std::filesystem::is_regular_file(mModelFilepath)) {
        mLogList << "[ERROR] - Uncorrect file type";
        return false;
    }

    if (!std::filesystem::exists(mTextureDirectory) || !std::filesystem::is_directory(mTextureDirectory)) {
        mLogList << "[WARNING] - The texture directory was not found, we use the relative model path";
        mTextureDirectory = mModelFilepath.parent_path();
    }

    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(mModelFilepath.string().c_str(),
                            aiProcess_GenSmoothNormals           |
                            aiProcess_ValidateDataStructure      |
                            aiProcess_CalcTangentSpace           |
                            aiProcess_FlipUVs                    |
                            aiProcess_RemoveRedundantMaterials   |
                            aiProcess_GenUVCoords                |
                            aiProcess_Triangulate                |
                            aiProcess_OptimizeMeshes             |
                            aiProcess_JoinIdenticalVertices      );    

    if (!pScene) {
        mLogList << "[ASSIMP ERROR] - " << importer.GetErrorString();
        return false;
    }            

    KitModelFile kmfFile;
    kmfFile.name = mModelName = std::filesystem::path(pScene->mRootNode->mName.C_Str()).replace_extension("").string();                    

    if (!std::filesystem::exists(mSaveDirectory) || !std::filesystem::is_directory(mSaveDirectory)) {
        mLogList << "[WARNING] - The save directory not found or uncorrect, we use the relative executable path";
        mSaveDirectory = "assets";
    }

    CreateDirectory(mSaveDirectory);

    std::filesystem::path material_save_directory(mSaveDirectory);
    material_save_directory.append("materials");
    mMaterialSavelDirectory = material_save_directory.string();

    std::filesystem::path texture_directory(save_directory);
    texture_directory.append("textures"); 
    mTextureSaveDirectory = texture_directory.string();      

    return true;
}

void ModelImportTool::CreateDirectory(const std::filesystem::path &path)
{
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
        mLogList << "[INFO] - A " << path << " was created\n";        
    }
}
