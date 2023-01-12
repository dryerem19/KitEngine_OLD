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
    mAabb = kmf.mAABB;
    mFilepath = kmf.filepath;

    mMeshes.reserve(kmf.meshes.size());
    for (auto& mesh : kmf.meshes)
    {
        mMeshes.emplace_back(std::make_unique<Render::KitStaticMesh>(mesh->vertices, mesh->indices));
        mMeshes.back()->name = mesh->name;
        mMeshes.back()->SetMaterial(mesh->material);
    }

    // btVector3 tmpTriangle[3];
    // pTempMesh = new btTriangleMesh(true, false);    
    // for (uint32_t iMesh = 0; iMesh < kmf.meshes.size(); iMesh++)
    // {
    //     for (uint32_t iTriangle = 0; iTriangle < kmf.meshes[iMesh]->indices.size(); iTriangle += 3)
    //     {
    //         for (uint32_t iVertex = 0; iVertex < 3; iVertex++)
    //         {
    //             int index = kmf.meshes[iMesh]->indices[iTriangle + iVertex];
    //             const auto& vertex = kmf.meshes[iMesh]->vertices[index];  

    //             tmpTriangle[iVertex].setX(vertex.mPosition.x);
    //             tmpTriangle[iVertex].setY(vertex.mPosition.x);
    //             tmpTriangle[iVertex].setZ(vertex.mPosition.x);           
    //         }
    //         pTempMesh->addTriangle(tmpTriangle[0], tmpTriangle[0], tmpTriangle[2], true);
    //     }
    // }

    // btVector3 aabbMin(-1000,-1000,-1000);
    // btVector3 aabbMax(1000,1000,1000);
    // pTempMesh->setPremadeAabb(aabbMin, aabbMax);
    // pTempMesh->setPremadeAabb(btVector3(kmf.mAABB.mMin.x, kmf.mAABB.mMin.y, kmf.mAABB.mMin.z),
    //     btVector3(kmf.mAABB.mMax.x, kmf.mAABB.mMax.y, kmf.mAABB.mMax.z));
}