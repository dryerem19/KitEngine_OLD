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
#include "KitStaticMesh.h"


#include "Shader.h"
#include "Transform.h"
#include "BaseCamera.h"

class Model
{
public:
    std::vector<std::unique_ptr<Render::KitStaticMesh>> mMeshes;
    std::string mFilepath;
    std::string mName;
    KMFAABB mAabb;
    btTriangleMesh* pTempMesh = nullptr;

    Transform mTransform;
public:
    void Deserialize(const std::string& filepath);

    void Draw(const std::shared_ptr<Shader>& shader, const BaseCamera& camera);
};