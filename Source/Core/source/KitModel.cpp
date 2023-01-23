/**
 * @file KitModel.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-21
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "KitModel.h"

KitModel::KitModel(const std::string &filepath)
    : mFilepath(filepath)
{
    
}

void KitModel::Load()
{
    if (!std::filesystem::exists(mFilepath))
    {
        return;     
    }

    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(mFilepath.c_str(),
                            aiProcess_GenSmoothNormals           |
                            aiProcess_ValidateDataStructure      |
                            aiProcess_CalcTangentSpace           |
                            aiProcess_FlipUVs                    |
                            aiProcess_RemoveRedundantMaterials   |
                            aiProcess_GenUVCoords                |
                            aiProcess_Triangulate                |
                            aiProcess_OptimizeMeshes             |
                            aiProcess_JoinIdenticalVertices      );    
}

void KitModel::ProccessNode(const aiNode *pNode, const aiScene *pScene)
{
    for (unsigned int iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
    {

    }

    for (unsigned int iNode = 0; iNode < pNode->mNumChildren; iNode++)
    {
        ProccessNode(pNode->mChildren[iNode], pScene);
    }
}

void KitModel::ProccessMesh(const aiMesh *pMesh, const aiScene *pScene)
{
    MeshData meshData;
    meshData.mName = pMesh->mName.C_Str();

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    meshData.mKitMesh.mVertices.reserve(pMesh->mNumVertices);
    for (unsigned int iVertex = 0; pMesh->mNumVertices; iVertex += 3)
    {
        const aiVector3D& Tri1Pos = pMesh->mVertices[iVertex];
        const aiVector3D& Tri2Pos = pMesh->mVertices[iVertex + 1];
        const aiVector3D& Tri3Pos = pMesh->mVertices[iVertex + 2];

        const aiVector3D& Tri1Nor = pMesh->mNormals[iVertex];
        const aiVector3D& Tri2Nor = pMesh->mNormals[iVertex + 1];
        const aiVector3D& Tri3Nor = pMesh->mNormals[iVertex + 2];

        const aiVector3D& Tri1Uvs = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;
        const aiVector3D& Tri2Uvs = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex + 1] : zero3D;
        const aiVector3D& Tri3Uvs = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex + 2] : zero3D;

        meshData.mKitMesh.mVertices.emplace_back(
            glm::vec3(Tri1Pos.x, Tri1Pos.y, Tri1Pos.z),
            glm::vec3(Tri1Nor.x, Tri1Nor.y, Tri1Nor.z),
            glm::vec2(Tri1Uvs.x, Tri1Uvs.y)
        );

        meshData.mKitMesh.mVertices.emplace_back(
            glm::vec3(Tri2Pos.x, Tri2Pos.y, Tri2Pos.z),
            glm::vec3(Tri2Nor.x, Tri2Nor.y, Tri2Nor.z),
            glm::vec2(Tri2Uvs.x, Tri2Uvs.y)
        );

        meshData.mKitMesh.mVertices.emplace_back(
            glm::vec3(Tri3Pos.x, Tri3Pos.y, Tri3Pos.z),
            glm::vec3(Tri3Nor.x, Tri3Nor.y, Tri3Nor.z),
            glm::vec2(Tri3Uvs.x, Tri3Uvs.y)
        );                            

        meshData.m_bulletMesh->addTriangle(btVector3(Tri1Pos.x, Tri1Pos.y, Tri1Pos.z),
            btVector3(Tri2Pos.x, Tri2Pos.y, Tri2Pos.z), btVector3(Tri3Pos.x, Tri3Pos.y, Tri3Pos.z));
    }   

    meshData.mKitMesh.mIndices.reserve(pMesh->mNumFaces * 3);
    for (unsigned int iFace = 0; iFace < pMesh->mNumFaces; iFace++)
    {
        const aiFace& face = pMesh->mFaces[iFace];
        for (unsigned int iIndex = 0; iIndex < face.mNumIndices; iIndex++)
        {
            meshData.mKitMesh.mIndices.emplace_back(face.mIndices[iIndex]);
        }        
    } 
}
