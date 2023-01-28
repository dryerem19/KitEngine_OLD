/**
 * @file Model.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "KitModelFile.h"
#include "Mesh.h"


#include "Shader.h"
#include "Transform.h"
#include "BaseCamera.h"

namespace Core
{
    class ResourceManager;
}

class Model
{
public:
    std::vector<std::unique_ptr<Mesh>> mMeshes;
    std::string mFilepath;
    std::string mName;
    KMFAABB mAabb;
    btTriangleMesh* pTempMesh = nullptr;

    Transform mTransform;

    std::string mDirectory;
public:
    void Deserialize(const std::string& filepath);


    void Load(const std::string& filepath);
    void ProcessNode(const aiNode* pNode, const aiScene* pScene);
    std::shared_ptr<Mesh> ProcessMesh(const aiMesh* pMesh, const aiScene* pScene);
    void ProcessMaterial(const aiMaterial* pMaterial, const aiScene* pScene);
    std::vector<std::shared_ptr<Render::KitTexture>> LoadTextures(const aiMaterial* pMaterial, aiTextureType type, const aiScene* pScene);


    void Draw(const std::shared_ptr<Shader>& shader, const BaseCamera& camera);
};