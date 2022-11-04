//
// Created by dryerem19 on 11/2/22.
//
#include "../../include/Utils/ModelLoader.h"

#include "Graphics/Vertex.h"
#include "Graphics/Components/ModelComponent.h"
#include "Core/Logger.h"

LevelEditor::Utils::ModelLoader::ModelLoader()
    : mNumVertices(0), mNumIndices(0) {

}

bool LevelEditor::Utils::ModelLoader::Import(const std::string &filepath) {

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

    if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
        KitEngine::Core::Log::Error("Assimp load error: {}", importer.GetErrorString());
        return false;
    }

    this->Clear();
    this->InitScene(pScene, filepath);
    if (mMeshEntryes.empty() || mVertices.empty() || mIndices.empty()) {
        return false;
    }

    return true;

}

void LevelEditor::Utils::ModelLoader::InitScene(const aiScene *pScene, const std::string &filepath) {

    mMeshEntryes.resize(pScene->mNumMeshes);

    this->CountVerticesAndIndices   (pScene);
    this->ReserveSpace              (      );
    this->InitAllMeshes             (pScene);

}

void LevelEditor::Utils::ModelLoader::CountVerticesAndIndices(const aiScene* pScene) {

    for (unsigned int iMesh = 0; iMesh < mMeshEntryes.size(); iMesh++) {
        mMeshEntryes[iMesh].MaterialIndex = pScene->mMeshes[iMesh]->mMaterialIndex;
        mMeshEntryes[iMesh].NumIndices    = pScene->mMeshes[iMesh]->mNumFaces * 3;
        mMeshEntryes[iMesh].BaseVertex    = mNumVertices;
        mMeshEntryes[iMesh].BaseIndex     = mNumIndices;

        mNumVertices += pScene->mMeshes[iMesh]->mNumVertices;
        mNumIndices  += mMeshEntryes[iMesh].NumIndices;
    }

}

void LevelEditor::Utils::ModelLoader::ReserveSpace() {


    mVertices   .reserve(mNumVertices);
    mIndices    .reserve(mNumIndices);

}

void LevelEditor::Utils::ModelLoader::InitAllMeshes(const aiScene *pScene) {

    for (unsigned int iMesh = 0; iMesh < pScene->mNumMeshes; iMesh++) {
        const aiMesh* pMesh = pScene->mMeshes[iMesh];
        if (pMesh != nullptr) {
            this->InitMesh(pMesh);
        }
    }

}

void LevelEditor::Utils::ModelLoader::InitMesh(const aiMesh *pMesh) {

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++) {
        const aiVector3D& pPos      = pMesh->mVertices[iVertex];
        const aiVector3D& pNormal   = pMesh->mNormals[iVertex];
        const aiVector3D& pTexCoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;

        mVertices.emplace_back(KitEngine::Graphics::Vertex{
                glm::vec3(pPos.x, pPos.y, pPos.z),
                glm::vec2(pTexCoord.x, pTexCoord.y),
                glm::vec3(pNormal.x, pNormal.y, pNormal.z),
        });
    }

    for (unsigned int iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
        const aiFace& pFace = pMesh->mFaces[iFace];

        if (pFace.mNumIndices != 3) {
            KitEngine::Core::Log::Warning("[ASSIMP] - The number of indexes is not equal to 3!");
        }

        mIndices.emplace_back(pFace.mIndices[0]);
        mIndices.emplace_back(pFace.mIndices[1]);
        mIndices.emplace_back(pFace.mIndices[2]);
    }

}

void LevelEditor::Utils::ModelLoader::Clear() {

    mIndices            .clear();
    mVertices           .clear();
    mMeshEntryes        .clear();

    mNumVertices = 0;
    mNumIndices  = 0;

}





