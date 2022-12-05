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

        this->ProcessAssimpNode(pScene->mRootNode, pScene, kmfFile.root.get());        

        kmfFile.header.version = 1;
        kmfFile.description.filepath = "test.kmf";
        kmfFile.Serialize();

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

        material->Serialize();

        // pMeshVisual->SetMaterial(material);

        return kmfMesh;
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
        std::filesystem::path texturePath = std::filesystem::path(directory);
        texturePath.concat(name.C_Str());

        /* Если текстура существует */
        if (std::filesystem::exists(texturePath))
        {
            /* Куда скопировать текстуру */
            std::filesystem::path copy_path("data/Textures/");
            copy_path.append(name.C_Str());

            /* Если текстура с таким именем уже существует по пути копирования */
            if (!std::filesystem::exists(copy_path))
            {
                // TODO: Сделать пользовательский диалог (окно) ImGui с сообщением о конфликте и предложением переименовать,
                // TODO: не забудь убрать восклицательный знак в условии
                std::filesystem::copy(texturePath, std::filesystem::path("data/Textures") / name.C_Str());
            }
        }

        return std::make_shared<Render::KitTexture>(texturePath.string(), 
                static_cast<Render::KitTextureType>(type));
    }
}