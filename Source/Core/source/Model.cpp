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
#include "ResourceManager.h"

void Model::Load(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filepath.c_str(),
                            aiProcess_GenSmoothNormals           |
                            aiProcess_ValidateDataStructure      |
                            aiProcess_CalcTangentSpace           |
                            aiProcess_FlipUVs                    |
                            aiProcess_RemoveRedundantMaterials   |
                            aiProcess_GenUVCoords                |
                            aiProcess_Triangulate                |
                            aiProcess_OptimizeMeshes             |
                            aiProcess_JoinIdenticalVertices      );

    if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    mFilepath = filepath;
    ProcessNode(pScene->mRootNode, pScene);
}

void Model::ProcessNode(const aiNode *pNode, const aiScene *pScene)
{
    // Обработка всех сеток в узле
    for (unsigned int iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
    {
        const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[iMesh]];
        mMeshes.emplace_back(ProcessMesh(pMesh, pScene));
    }

    // Обработка всех дочерних узлов
    for (unsigned int iNode = 0; iNode < pNode->mNumChildren; iNode++)
    {
        const aiNode* pChild = pNode->mChildren[iNode];
        ProcessNode(pChild, pScene);
    }
}

std::shared_ptr<Mesh> Model::ProcessMesh(const aiMesh *pMesh, const aiScene *pScene)
{
    std::vector<KitVertex> vertices;
    vertices.reserve(pMesh->mNumVertices);

    std::vector<unsigned int> indices;
    indices.reserve(pMesh->mNumFaces * 3);

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    for (unsigned int iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++)
    {
        const aiVector3D& position = pMesh->mVertices[iVertex];
        const aiVector3D& norcoord = pMesh->mNormals[iVertex];
        const aiVector3D& texcoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;

        vertices.emplace_back(glm::vec3(position.x, position.y, position.z), 
                              glm::vec3(norcoord.x, norcoord.y, norcoord.z), glm::vec2(texcoord.x, texcoord.y));
    }

    for (unsigned int iFace = 0; iFace < pMesh->mNumFaces; iFace++)
    {
        const aiFace& face = pMesh->mFaces[iFace];
        indices.emplace_back(face.mIndices[0]);
        indices.emplace_back(face.mIndices[1]);
        indices.emplace_back(face.mIndices[2]);
    }

    auto kitMesh = std::make_shared<Mesh>(vertices, indices);
    if (pMesh->mMaterialIndex >= 0) {
        const aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
        ProcessMaterial(pMesh, pScene, *kitMesh);
    }

    return kitMesh;
}

void Model::ProcessMaterial(const aiMesh* p_aiMesh, const aiScene* p_aiScene, Mesh& kitMesh)
{
    const aiMaterial* p_aiMaterial = p_aiScene->mMaterials[p_aiMesh->mMaterialIndex];
    if (!p_aiMaterial) {
        return;
    }

    float shininess;
    if (AI_SUCCESS == p_aiMaterial->Get(AI_MATKEY_SHININESS, shininess)) {
        kitMesh.mMaterial.mShininess = shininess;
    }

    // Загрузка диффузных карт
    LoadTextures(p_aiMaterial, aiTextureType_DIFFUSE, p_aiScene, kitMesh);
}

void Model::LoadTextures(const aiMaterial *pMaterial, aiTextureType type, const aiScene* pScene, Mesh& kitMesh)
{
    aiString textureFile;
    if (AI_SUCCESS == pMaterial->GetTexture(type, 0, &textureFile)) 
    {
        if (const aiTexture* pTexture = pScene->GetEmbeddedTexture(textureFile.C_Str()))
        {
            return;
        } 
        else 
        {
            std::string texturePath = textureFile.C_Str();
            if (!IsPathExist(texturePath)) {
                std::string directoryTexturePath = mFilepath.substr(0, mFilepath.find_last_of('/')) + '/' + texturePath;
                if (!IsPathExist(directoryTexturePath)) {
                    return;
                }
                texturePath = directoryTexturePath;
            }
            auto texture = Core::ResourceManager::Instance().GetTexture(texturePath);
            if (texture) {
                kitMesh.mMaterial.mDiffuseTex = texture;
            }
        }
    }
}

bool Model::IsPathExist(const std::string &path) const
{
    return std::filesystem::exists(path);
}