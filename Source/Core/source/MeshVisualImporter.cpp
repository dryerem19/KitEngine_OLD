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

        std::string rootNodeName = std::filesystem::path( pScene->mRootNode->mName.C_Str() )
                                        .replace_extension( "" )
                                        .string();                                

        m_pRootEntity = new BaseEntity( rootNodeName );
        this->ProcessAssimpNode( pScene->mRootNode, pScene, m_pRootEntity );        
    }

    void MeshVisualImporter::ProcessAssimpNode( const aiNode* pNode, const aiScene* pScene, BaseEntity* pRootEntity )
    {
        // Обрабатываем все меши ноды
        for (uint32_t iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
        {   
            const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[iMesh]];

            BaseEntity* pChildEntity = new BaseEntity();
            pChildEntity->SetName(pMesh->mName.C_Str());
            pChildEntity->SetMesh(this->ProcessAssimpMesh(pMesh, pScene));
            pRootEntity->LinkChild(pChildEntity);
        }

        // Рекурсивно обрабатываем все дочерние ноды
        for (uint32_t iChild = 0; iChild < pNode->mNumChildren; iChild++)
        {
            const aiNode* pChildNode = pNode->mChildren[iChild];
            BaseEntity* pChildEntity = new BaseEntity(pChildNode->mName.C_Str());
            pRootEntity->LinkChild(pChildEntity);
            this->ProcessAssimpNode(pNode->mChildren[iChild], pScene, pChildEntity);
        }        
    }

    Render::KitStaticMesh* MeshVisualImporter::ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene)
    {
        const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

        // Создаём вектор под вершины и резервируем место
        std::vector<Render::KitVertex> vertices;
        vertices.reserve(pMesh->mNumVertices);

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
            vertices.emplace_back(Render::KitVertex{
                glm::vec3(pos.x, pos.y, pos.z),
                glm::vec3(nor.x, nor.y, nor.z),
                glm::vec2(tex.x, tex.y)
            });
        }

        // Создаём вектор под индексы и резервируем место
        std::vector<uint32_t> indices;
        indices.reserve(pMesh->mNumFaces * 3);

        // Обходим все треугольники меша
        for (uint32_t iFace = 0; iFace < pMesh->mNumFaces; iFace++) {
            const aiFace& face = pMesh->mFaces[iFace];

            // Записываем индексы треугольника в вектор
            indices.emplace_back(face.mIndices[0]);
            indices.emplace_back(face.mIndices[1]);
            indices.emplace_back(face.mIndices[2]);
        }

        Render::KitStaticMesh* pMeshVisual = new Render::KitStaticMesh(vertices, indices);

        // Создаём новый материал (по умолчанию)
        std::shared_ptr<Render::KitMaterial> material = std::make_shared<Render::KitMaterial>();

        // Если на меш назначен материал, загружаем его
        if (pMesh->mMaterialIndex >= 0)
        {
            // Удаляем имя файла из пути, чтобы получить директорию
            std::filesystem::path directory = std::filesystem::path(mFilepath);
            directory.remove_filename();
            
            // Обрабатываем материал
            this->ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex], 
                directory.string(), material.get());
        }

        pMeshVisual->SetMaterial(material);

        return pMeshVisual;
    }

    void MeshVisualImporter::ProcessAssimpMaterial(const aiMaterial* pMaterial, const std::string& directory, Render::KitMaterial* kitMaterial)
    {
        // Загружаем имя материала
        kitMaterial->mName = pMaterial->GetName().C_Str();

        // Загружаем diffuse текстуры 
        kitMaterial->mMainDiffuseTexture = this->LoadMaterialTextures(pMaterial, aiTextureType_DIFFUSE, directory);        
    }

    std::shared_ptr<Render::KitTexture> MeshVisualImporter::LoadMaterialTextures(const aiMaterial* pMaterial, 
    aiTextureType type, const std::string& directory)
    {
        // Получаем имя текстуры
        aiString name;
        pMaterial->GetTexture(type, 0, &name);

        /*
        * Мы предпологаем, что текстура находится в той же директории, где и модель,
        * поэтому directory - это директория модели. 
        * Мы объединяем её с именем текстуры, чтобы получить предпологаемый путь. 
        */
        std::filesystem::path filepath = std::filesystem::path(directory);
        filepath.concat(name.C_Str());

        return std::make_shared<Render::KitTexture>(filepath.string(), 
                static_cast<Render::KitTextureType>(type));
    }
}