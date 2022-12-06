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

        KitModelFile kmfFile;
        kmfFile.root = std::make_unique<KMFNode>();
        kmfFile.root->name = mModelName = std::filesystem::path(pScene->mRootNode->mName.C_Str()).replace_extension("").string();                                

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

        this->ProcessAssimpNode(pScene->mRootNode, pScene, kmfFile.root.get());      

        kmfFile.header.version = 1;
        kmfFile.description.filepath = "test.kmf";
        
        std::filesystem::path model_save_path(save_directory);
        model_save_path.append(mModelName).concat(".kmf");
        kmfFile.Serialize(model_save_path.string());

     }

    void MeshVisualImporter::ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, KMFNode* pKmfNode)
    {
        if (pNode->mNumMeshes > 0)
        {
            pKmfNode->meshes.reserve(pNode->mNumMeshes);
        }

        // Обрабатываем все меши ноды
        for (uint32_t iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
        {   
            const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[iMesh]];
            pKmfNode->meshes.emplace_back(ProcessAssimpMesh(pMesh, pScene));
        }

        // Рекурсивно обрабатываем все дочерние ноды
        for (uint32_t iChild = 0; iChild < pNode->mNumChildren; iChild++)
        {
            const aiNode* pChildNode = pNode->mChildren[iChild];

            std::shared_ptr<KMFNode> childKmfNode = std::make_shared<KMFNode>();
            childKmfNode->name = pChildNode->mName.C_Str();
            childKmfNode->pParent = pKmfNode;
            pKmfNode->children.emplace_back(childKmfNode);

            this->ProcessAssimpNode(pNode->mChildren[iChild], pScene, childKmfNode.get());
        }        
    }

    KMFMesh MeshVisualImporter::ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene)
    {
        KMFMesh kmfMesh;
        kmfMesh.name = pMesh->mName.C_Str();
        kmfMesh.vertices.reserve(pMesh->mNumVertices);
        kmfMesh.indices.reserve(pMesh->mNumFaces * 3);

        const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

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
            kmfMesh.vertices.emplace_back(Render::KitVertex{
                glm::vec3(pos.x, pos.y, pos.z),
                glm::vec3(nor.x, nor.y, nor.z),
                glm::vec2(tex.x, tex.y)
            });
        }

        // Обходим все треугольники меша
        for (uint32_t iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
            const aiFace& face = pMesh->mFaces[iFace];

            // Записываем индексы треугольника в вектор
            kmfMesh.indices.emplace_back(face.mIndices[0]);
            kmfMesh.indices.emplace_back(face.mIndices[1]);
            kmfMesh.indices.emplace_back(face.mIndices[2]);
        }

        // Если на меш назначен материал, загружаем его
        if (pMesh->mMaterialIndex >= 0)
        {
            // Удаляем имя файла из пути, чтобы получить директорию
            std::filesystem::path directory = std::filesystem::path(mFilepath);
            directory.remove_filename();
            
            kmfMesh.material = ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex], 
                directory.string());
        }

        return kmfMesh;
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
        if (!std::filesystem::exists(diffuse_texture_path))
        {
            diffuse_texture_path.clear();
            diffuse_texture_path.append(directory).append(texture_name.C_Str());

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