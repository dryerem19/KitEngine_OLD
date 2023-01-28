/**
 * @file MeshVisualImporter.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#include "pch.h"
#include "MeshVisualImporter.h"
#include "Logger.h"

namespace Core
{
    void MeshVisualImporter::LoadVisual( void )
    {
        assert(!mFilepath.empty());       

        // Создаём объект импортера данных assimp'а
        Assimp::Importer importer;

        // Считываем данные файлы в сцену assimp'а
        const aiScene* pScene = importer.ReadFile(mFilepath.string().c_str(),
                                aiProcess_GenSmoothNormals           |
                                aiProcess_ValidateDataStructure      |
                                aiProcess_CalcTangentSpace           |
                                aiProcess_FlipUVs                    |
                                aiProcess_RemoveRedundantMaterials   |
                                aiProcess_GenUVCoords                |
                                aiProcess_Triangulate                |
                                aiProcess_OptimizeMeshes             |
                                aiProcess_JoinIdenticalVertices      );

        if (!pScene) {
            Core::Log::Error("Assimp error: {} - {}", mFilepath.string().c_str(), importer.GetErrorString());
            return;
        }

        KitModelFile kmfFile;
        kmfFile.name = mModelName = std::filesystem::path(pScene->mRootNode->mName.C_Str()).replace_extension("").string();                                

        /* Cоздаём папки для сохранения */
        std::filesystem::path save_directory("data");
        save_directory.append(mModelName);
        mModelSaveDirectory = save_directory.string();

        std::filesystem::path material_directory(save_directory);
        material_directory.append("materials");
        mMaterialSavelDirectory = material_directory.string();

        std::filesystem::path texture_directory(save_directory);
        texture_directory.append("textures"); 
        mTextureSaveDirectory = texture_directory.string();

        if (!std::filesystem::exists(save_directory))
        {
            std::filesystem::create_directories(save_directory);
        }
        
        if (!std::filesystem::exists(material_directory))
        {
            std::filesystem::create_directories(material_directory);
        }

        if (!std::filesystem::exists(texture_directory))
        {
            std::filesystem::create_directories(texture_directory);
        }

        this->ParseMeshes(pScene, kmfFile);


        
        std::filesystem::path model_save_path(save_directory);
        model_save_path.append(mModelName).concat(".kmf");
        kmfFile.Serialize(model_save_path.string());

     }

     void MeshVisualImporter::ParseMeshes(const aiScene* pScene, KitModelFile& kmf)
     {
        kmf.meshes.reserve(pScene->mNumMeshes);
        for (uint32_t iMesh = 0; iMesh < pScene->mNumMeshes; iMesh++)
        {
            kmf.meshes.emplace_back(std::make_unique<KMFMesh>());

            const aiMesh* pMesh = pScene->mMeshes[iMesh];
            const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

            kmf.meshes[iMesh]->name = pMesh->mName.C_Str();
            kmf.meshes[iMesh]->vertices.reserve(pMesh->mNumVertices);
            kmf.meshes[iMesh]->indices.reserve(pMesh->mNumFaces * 3);

            // Обходим все вершины меша
            for (uint32_t iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++) 
            {
                // Получаем позицию, нормаль и текстурную координату вершины
                const aiVector3D& pos = pMesh->mVertices[iVertex];
                const aiVector3D& nor = pMesh->mNormals[iVertex];

                // Если у меша нет текстурных координат, назначаем нулевые текстурные координаты
                const aiVector3D& tex = pMesh->HasTextureCoords(0) 
                    ? pMesh->mTextureCoords[0][iVertex] : zero3D;

                // Заносим вершину в вектор
                kmf.meshes[iMesh]->vertices.emplace_back(KitVertex{
                    glm::vec3(pos.x, pos.y, pos.z),
                    glm::vec3(nor.x, nor.y, nor.z),
                    glm::vec2(tex.x, tex.y)
                });
            }

            // Обходим все треугольники меша
            for (uint32_t iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
                const aiFace& face = pMesh->mFaces[iFace];

                // Записываем индексы треугольника в вектор
                kmf.meshes[iMesh]->indices.emplace_back(face.mIndices[0]);
                kmf.meshes[iMesh]->indices.emplace_back(face.mIndices[1]);
                kmf.meshes[iMesh]->indices.emplace_back(face.mIndices[2]);
            }

            // Если на меш назначен материал, загружаем его
            if (pMesh->mMaterialIndex >= 0)
            {
                // Удаляем имя файла из пути, чтобы получить директорию
                std::filesystem::path directory = std::filesystem::path(mFilepath);
                directory.remove_filename();
                
                kmf.meshes[iMesh]->material = ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex], 
                    directory.string());
            }            
        }
     }

    std::string MeshVisualImporter::ProcessAssimpMaterial(const aiMaterial* pMaterial, const std::string& directory)
    {
        assert(pMaterial && "pMaterial should not be empty!");
        std::string material_name(pMaterial->GetName().C_Str());

        aiString texture_name;
        aiReturn aiResult = pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texture_name);


        /**
         * Assimp может хранить путь к текстуре или имя текстуры, которое также может быть относительным путём.
         * Мы проверяем этот факт в условии и если текстуры по такому пути не существует, то предпологаем, что
         * текстура лежит в директории модели
         */
        std::filesystem::path diffuse_texture_path(texture_name.C_Str());
        std::cout << diffuse_texture_path.string() << std::endl;
        if (!std::filesystem::exists(diffuse_texture_path))
        {
            diffuse_texture_path.clear();
            //diffuse_texture_path.append(directory).append(texture_name.C_Str());
            diffuse_texture_path.append(mTextureDirectory).append(texture_name.C_Str());

            std::filesystem::path diffuse_texture_save_path(mTextureSaveDirectory);
            diffuse_texture_save_path.append(texture_name.C_Str());
            if (std::filesystem::exists(diffuse_texture_path) && !std::filesystem::exists(diffuse_texture_save_path))
            {
                std::filesystem::copy_file(diffuse_texture_path, diffuse_texture_save_path);
            }
            diffuse_texture_path = diffuse_texture_save_path;
        }
        std::filesystem::path material_save_path(mMaterialSavelDirectory);
        material_save_path.append(material_name).concat(".material");
 
        if (std::find(mMaterialFilepathCache.begin(), mMaterialFilepathCache.end(), material_save_path) != mMaterialFilepathCache.end())
        {
            return material_save_path.string();
        }

        mMaterialFilepathCache.emplace_back(material_save_path.string());
        KitMaterialFile material(material_name, diffuse_texture_path.string());
        material.Serialize(material_save_path.string());  
        return material_save_path.string();      
    }
}