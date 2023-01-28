/**
 * @file ModelImportTool.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ModelImportTool.h"

bool ModelImportTool::Import()
{
    if (!fs::exists(mModelFilepath)) {
        mLogList << "[ERROR] - File not found\n";
        return false;
    }

    if (!fs::exists(mTextureDirectory) || !fs::is_directory(mTextureDirectory)) {
        mLogList << "[WARNING] - The texture directory was not found, we use the relative model path\n";
        mTextureDirectory = mModelFilepath.parent_path();
    }

    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(mModelFilepath.string().c_str(),
                            aiProcess_GenSmoothNormals           |
                            aiProcess_ValidateDataStructure      |
                            aiProcess_CalcTangentSpace           |
                            aiProcess_FlipUVs                    |
                            aiProcess_RemoveRedundantMaterials   |
                            aiProcess_GenUVCoords                |
                            aiProcess_Triangulate                |
                            aiProcess_OptimizeMeshes             |
                            aiProcess_JoinIdenticalVertices      |
                            aiProcess_GenBoundingBoxes           );

    if (!pScene) {
        mLogList << "[ASSIMP ERROR] - " << importer.GetErrorString() << "\n";
        return false;
    }            

    mLogList << "[INFO] - Number of meshes: " << pScene->mNumMeshes << "\n";
    mKmfFile.meshes.reserve(pScene->mNumMeshes);

    std::string name = fs::path(pScene->mRootNode->mName.C_Str()).replace_extension("").string();
    if (name == "RootNode") {
        name = mModelFilepath.filename().replace_extension("").string();
    }

    if (!fs::exists(mSaveDirectory) || !fs::is_directory(mSaveDirectory)) {
        mLogList << "[WARNING] - The save directory not found or uncorrect, we use the relative executable path\n";
        mSaveDirectory = "imported";
    }
    mSaveDirectory.append(name);

    // Директория импорта
    CreateDirectory(mSaveDirectory);

    // Директория с материалами
    mMaterialSaveDirectory = mSaveDirectory;
    mMaterialSaveDirectory.append("materials");
    CreateDirectory(mMaterialSaveDirectory);

    // Директория с текстурами
    mTextureSaveDirectory = mSaveDirectory;
    mTextureSaveDirectory.append("textures");
    CreateDirectory(mTextureSaveDirectory);

    mKmfFile.name = name;
    ParseMeshes(pScene);
    return true;
}

void ModelImportTool::Save()
{
    fs::path saved_path = mSaveDirectory;
    saved_path.append(mKmfFile.name);
    mKmfFile.Serialize(saved_path.string());
    mLogList << "[INFO] - KMF File saved: " << saved_path.string() << "\n";
}

void ModelImportTool::CreateDirectory(const fs::path &path)
{
    if (!fs::exists(path)) {
        fs::create_directories(path);
        mLogList << "[INFO] - A " << path << " was created\n";
    }
}

void ModelImportTool::ParseMeshes(const aiScene *pScene)
{
    assert(pScene && "pScene should not be empty!");

    for (uint32_t iMesh = 0; iMesh < pScene->mNumMeshes; iMesh++)
    {
        mKmfFile.meshes.emplace_back(std::make_unique<KMFMesh>());

        const aiMesh* pMesh = pScene->mMeshes[iMesh];
        const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

        // if (mKmfFile.mAABB.mMin.x > pMesh->mAABB.mMin.x ||
        //     mKmfFile.mAABB.mMin.y > pMesh->mAABB.mMin.y ||
        //     mKmfFile.mAABB.mMin.z > pMesh->mAABB.mMin.z) {
        //         mKmfFile.mAABB.mMin.x = pMesh->mAABB.mMin.x;
        //         mKmfFile.mAABB.mMin.y = pMesh->mAABB.mMin.y;
        //         mKmfFile.mAABB.mMin.z = pMesh->mAABB.mMin.z;
        // }

        // if (mKmfFile.mAABB.mMax.x < pMesh->mAABB.mMax.x ||
        //     mKmfFile.mAABB.mMax.y < pMesh->mAABB.mMax.y ||
        //     mKmfFile.mAABB.mMax.z < pMesh->mAABB.mMax.z) {
        //         mKmfFile.mAABB.mMax.x = pMesh->mAABB.mMax.x;
        //         mKmfFile.mAABB.mMax.y = pMesh->mAABB.mMax.y;
        //         mKmfFile.mAABB.mMax.z = pMesh->mAABB.mMax.z;
        // }        
        // mKmfFile.mAABB.mCenter = 0.5f * (mKmfFile.mAABB.mMin + mKmfFile.mAABB.mMax);
        // mKmfFile.mAABB.mExtents = 0.5f * (mKmfFile.mAABB.mMax + mKmfFile.mAABB.mMin);

        mKmfFile.meshes[iMesh]->name = pMesh->mName.C_Str();
        mKmfFile.meshes[iMesh]->vertices.reserve(pMesh->mNumVertices);
        mKmfFile.meshes[iMesh]->indices.reserve(pMesh->mNumFaces * 3);

        // Обходим все вершины меша
        for (uint32_t iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++) 
        {
            // Получаем позицию, нормаль и текстурную координату вершины
            const aiVector3D& pos = pMesh->mVertices[iVertex];
            const aiVector3D& nor = pMesh->mNormals[iVertex];

            // Если у меша нет текстурных координат, назначаем нулевые текстурные координаты
            const aiVector3D& tex = pMesh->HasTextureCoords(0) 
                ? pMesh->mTextureCoords[0][iVertex] : zero3D;

            mKmfFile.mAABB.mMin = glm::min(mKmfFile.mAABB.mMin, glm::vec3(pos.x, pos.y, pos.z));
            mKmfFile.mAABB.mMax = glm::max(mKmfFile.mAABB.mMax, glm::vec3(pos.x, pos.y, pos.z));

            // Заносим вершину в вектор
            mKmfFile.meshes[iMesh]->vertices.emplace_back(KitVertex{
                glm::vec3(pos.x, pos.y, pos.z),
                glm::vec3(nor.x, nor.y, nor.z),
                glm::vec2(tex.x, tex.y)
            });
        }

        // Обходим все треугольники меша
        for (uint32_t iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
            const aiFace& face = pMesh->mFaces[iFace];

            if (face.mNumIndices != 3) {
                mLogList << "[WARNING] - Uncorrect number of indicies in face!\n"; 
            }

            // Записываем индексы треугольника в вектор
            mKmfFile.meshes[iMesh]->indices.emplace_back(face.mIndices[0]);
            mKmfFile.meshes[iMesh]->indices.emplace_back(face.mIndices[1]);
            mKmfFile.meshes[iMesh]->indices.emplace_back(face.mIndices[2]);
        }

        // Если на меш назначен материал, загружаем его
        if (pMesh->mMaterialIndex >= 0) {            
            mKmfFile.meshes[iMesh]->material = ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex]);
        } else {
            mLogList << "[INFO] - Undefined material for mesh: " << pMesh->mName.C_Str() << "\n";
        }
    }
}

std::string ModelImportTool::ProcessAssimpMaterial(const aiMaterial *pMaterial)
{
    assert(pMaterial && "pMaterial should not be empty!");

    std::string material_name(pMaterial->GetName().C_Str());
    aiString diffuse_texture_name;
    if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &diffuse_texture_name) != AI_SUCCESS) {
        mLogList << "[WARNING] - The name of the texture was not found, I'm trying to fix it by substituting the name of the material\n";
        diffuse_texture_name = material_name.c_str();
    }

    // Получаем путь к текстуре типа diffuse
    fs::path diffuse_texture_path(mTextureDirectory);
    diffuse_texture_path.append(diffuse_texture_name.C_Str());
    if (!fs::exists(diffuse_texture_path)) {
        mLogList << "[WARNING] - Undefined diffuse texture by path: " << diffuse_texture_path.string().c_str() << "\n";
    }

    fs::path new_texture_path(mTextureSaveDirectory);
    new_texture_path.append(diffuse_texture_name.C_Str());
    if (!fs::exists(new_texture_path) && fs::exists(diffuse_texture_path)) {
        fs::copy_file(diffuse_texture_path, new_texture_path);
        mLogList << "[INFO] - The texture was copied to: " << new_texture_path.string() << "\n";
    }

    // Сохраняем материал
    fs::path material_save_path(mMaterialSaveDirectory);
    material_save_path.append(material_name).concat(".material");
    if (!fs::exists(material_save_path)) {
        KitMaterialFile material(material_name, new_texture_path.string());
        material.Serialize(material_save_path.string());
    }

    return material_save_path.string();
}
