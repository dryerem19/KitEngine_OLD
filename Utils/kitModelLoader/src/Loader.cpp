//
// Created by dryerem19 on 11/5/22.
//
#include "pch.h"
#include "Loader.h"

void kitModelLoader::Loader::Import(const std::string &filepath) {

    Assimp::Importer importer;

    const aiScene *pScene = nullptr;
    pScene = importer.ReadFile(filepath,
                               aiProcess_GenSmoothNormals           |
                               aiProcess_ValidateDataStructure      |
                               aiProcess_CalcTangentSpace           |
                               aiProcess_RemoveRedundantMaterials   |
                               aiProcess_GenUVCoords                |
                               aiProcess_TransformUVCoords          |
                               aiProcess_Triangulate                |
                               aiProcess_OptimizeMeshes             |
                               aiProcess_JoinIdenticalVertices      |
                               aiProcess_SortByPType                );

//    if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
//        KitEngine::Core::Log::Error("Assimp load error: {}", importer.GetErrorString());
//    }

    this->Clear();
    this->InitScene(pScene, filepath);

}

void kitModelLoader::Loader::InitScene(const aiScene *pScene, const std::string &filepath) {

    mMeshes.resize(pScene->mNumMeshes);

    uint32_t verticesCount = 0;
    uint32_t indicesCount  = 0;

    this->CountVerticesAndIndices   (pScene, verticesCount, indicesCount);
    this->ReserveSpace              (verticesCount, indicesCount);
    this->InitAllMeshes             (pScene);

}

void kitModelLoader::Loader::CountVerticesAndIndices(const aiScene *pScene, uint32_t& verticesCount,
                                                     uint32_t& indicesCount) {

    for (uint32_t iMesh = 0; iMesh < mMeshes.size(); iMesh++) {
        mMeshes[iMesh].MaterialIndex = pScene->mMeshes[iMesh]->mMaterialIndex;
        mMeshes[iMesh].NumIndices    = pScene->mMeshes[iMesh]->mNumFaces * 3;
        mMeshes[iMesh].BaseVertex    = verticesCount;
        mMeshes[iMesh].BaseIndex     = indicesCount;

        verticesCount += pScene->mMeshes[iMesh]->mNumVertices;
        indicesCount  += mMeshes[iMesh].NumIndices;
    }

}

void kitModelLoader::Loader::ReserveSpace(uint32_t& verticesCount, uint32_t& indicesCount) {

    mVertices   .reserve(verticesCount);
    mIndices    .reserve(indicesCount);

}

void kitModelLoader::Loader::InitAllMeshes(const aiScene *pScene) {

    for (uint32_t iMesh = 0; iMesh < pScene->mNumMeshes; iMesh++) {
        const aiMesh* pMesh = pScene->mMeshes[iMesh];
        if (pMesh != nullptr) {
            this->InitMesh(pMesh);
        }
    }

}

void kitModelLoader::Loader::InitMesh(const aiMesh *pMesh) {

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++) {
        const aiVector3D& pPos      = pMesh->mVertices[iVertex];
        const aiVector3D& pNormal   = pMesh->mNormals[iVertex];
        const aiVector3D& pTexCoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;

        mVertices.emplace_back(Vertex{
            pPos, pNormal, aiVector2D(pTexCoord.x, pTexCoord.y)
        });
    }

    for (uint32_t iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
        const aiFace& pFace = pMesh->mFaces[iFace];

//        if (pFace.mNumIndices != 3) {
//            KitEngine::Core::Log::Warning("[ASSIMP] - The number of indexes is not equal to 3!");
//        }

        mIndices.emplace_back(pFace.mIndices[0]);
        mIndices.emplace_back(pFace.mIndices[1]);
        mIndices.emplace_back(pFace.mIndices[2]);
    }

}

void kitModelLoader::Loader::Clear() {

    mIndices            .clear();
    mVertices           .clear();
    mMeshes             .clear();

}
