//
// Created by dryerem19 on 11/5/22.
//
#include "pch.h"
#include "Loader.h"

void kitModelLoader::Loader::Import(const std::filesystem::path& filepath) {

    Assimp::Importer importer;

    const aiScene *pScene;
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

void kitModelLoader::Loader::InitScene(const aiScene *pScene, const std::filesystem::path& filepath) {

    mMeshes.resize(pScene->mNumMeshes);

    uint32_t verticesCount = 0;
    uint32_t indicesCount  = 0;

    this->CountVerticesAndIndices   (pScene, verticesCount, indicesCount);
    this->ReserveSpace              (verticesCount, indicesCount);
    this->InitAllMeshes             (pScene);
    this->InitAllMaterials          (pScene, filepath);

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
            this->InitMesh(pMesh, pScene);
        }
    }

}

void kitModelLoader::Loader::InitMesh(const aiMesh *pMesh, const aiScene* pScene) {

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++) {
        const aiVector3D& pPos      = pMesh->mVertices[iVertex];
        const aiVector3D& pNormal   = pMesh->mNormals[iVertex];
        const aiVector3D& pTexCoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;

        mVertices.emplace_back(kitVertex{
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

void kitModelLoader::Loader::InitAllMaterials(const aiScene* pScene, const std::filesystem::path& filepath) {

    for (auto& mesh : mMeshes) {
        if (mesh.MaterialIndex >= 0) {
            const aiMaterial* pMaterial = pScene->mMaterials[mesh.MaterialIndex];
            this->InitMaterial(pMaterial, filepath);
        }
    }

}

void kitModelLoader::Loader::InitMaterial(const aiMaterial* pMaterial, const std::filesystem::path& filepath) {

    if (!pMaterial) {
        return;
    }

    kitMaterial material;

    InitTextures(pMaterial, aiTextureType_DIFFUSE     ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_SPECULAR    ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_AMBIENT     ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_EMISSIVE    ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_HEIGHT      ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_NORMALS     ,   material, filepath);
    InitTextures(pMaterial, aiTextureType_SHININESS   ,   material, filepath);

    aiString matName;
    if ((AI_SUCCESS == pMaterial->Get(AI_MATKEY_NAME, matName)) && matName.length > 0) {
        material.Name = matName.data;
    }

    pMaterial->Get(
            AI_MATKEY_COLOR_AMBIENT,
            material.Ambient
    );
    pMaterial->Get(
            AI_MATKEY_COLOR_DIFFUSE,
            material.Diffuse
    );
    pMaterial->Get(
            AI_MATKEY_COLOR_SPECULAR,
            material.Specular
    );
    pMaterial->Get(
            AI_MATKEY_COLOR_EMISSIVE,
            material.Emmissie
    );
    pMaterial->Get(
            AI_MATKEY_COLOR_TRANSPARENT,
            material.Transparent
    );


    mMaterials.emplace_back(material);

}

void kitModelLoader::Loader::InitTextures(const aiMaterial *pMaterial, const aiTextureType type,
                                          kitMaterial& material, const std::filesystem::path& filepath) {

    for (uint32_t iTexture = 0; iTexture < pMaterial->GetTextureCount(type); iTexture++) {

        aiString path;
        if (AI_FAILURE == pMaterial->GetTexture(type, iTexture, &path)) {
            continue;
        }

        if (path.length <= 0) {
            continue;
        }

        std::filesystem::path fullpath(filepath);
        fullpath.remove_filename();
        fullpath.concat(std::begin(path.data), std::begin(path.data) + path.length);

       // std::cout << "LOADER: " << path.data << std::endl;

        if (std::filesystem::exists(fullpath)) {
            material.mTextures.emplace_back(
                    kitTexture((kitTextureType) type, fullpath)
            );
        }
        else {
            // TODO: LOG
        }

    }

}


void kitModelLoader::Loader::Clear() {

    mIndices            .clear();
    mVertices           .clear();
    mMeshes             .clear();

}
