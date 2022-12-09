/**
 * @file Model.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Model.h"

void Model::Deserialize(const std::string& filepath)
{
    KitModelFile kmf;
    kmf.Deserialize(filepath);

    mName = kmf.name;
    mFilepath = kmf.filepath;

    mMeshes.reserve(kmf.meshes.size());
    for (auto& mesh : kmf.meshes)
    {
        mMeshes.emplace_back(std::make_unique<Render::KitStaticMesh>(mesh->vertices, mesh->indices));
        mMeshes.back()->name = mesh->name;
        mMeshes.back()->SetMaterial(mesh->material);
    }
}