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

#include "KitMaterial.h"

namespace Core
{
    class ResourceManager;
}

class Model
{
private:
    
public:
    //std::vector<std::unique_ptr<Mesh>> mMeshes;
    std::vector<std::shared_ptr<Mesh>> mMeshes;
    std::string mFilepath;
    std::string mName;
    KMFAABB mAabb;

    Transform mTransform;

    std::string mDirectory;
public:
    void Load(const std::string& filepath);
    void ProcessNode(const aiNode* pNode, const aiScene* pScene);

    std::shared_ptr<Mesh> ProcessMesh(const aiMesh* pMesh, const aiScene* pScene);



    void ProcessMaterial(const aiMesh* p_aiMesh, const aiScene* p_aiScene, Mesh& kitMesh);
    void LoadTextures(const aiMaterial* pMaterial, aiTextureType type, const aiScene* pScene, Mesh& kitMesh);
    bool IsPathExist(const std::string& path) const;
};