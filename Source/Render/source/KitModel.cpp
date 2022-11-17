#include "RenderPch.h"
#include "KitModel.h"

Render::KitModel::KitModel(const KitObject& attachedObject, const std::string& filepath)
    : KitSceneNode(attachedObject)
{
    this->Init(filepath);
}

void Render::KitModel::Init(const std::string& filepath)
{
    mFilepath = filepath;

    // Создаём объект импортера данных assimp'а
    Assimp::Importer importer;

    // Считываем данные файлы в сцену assimp'а
    const aiScene *p_assimpScene = nullptr;
    p_assimpScene = importer.ReadFile(filepath.c_str(),
                               aiProcess_GenSmoothNormals           |
                               aiProcess_ValidateDataStructure      |
                               aiProcess_CalcTangentSpace           |
                               aiProcess_FlipUVs                    |
                               aiProcess_RemoveRedundantMaterials   |
                               aiProcess_GenUVCoords                |
                               aiProcess_Triangulate                |
                               aiProcess_OptimizeMeshes             |
                               aiProcess_JoinIdenticalVertices      );

    mName = std::filesystem::path(p_assimpScene->mRootNode->mName.C_Str())
                                    .replace_extension("")
                                    .string();

    // Обрабатываем все ноды сцены начиная с родительской
    this->ProcessAssimpNode(p_assimpScene->mRootNode, p_assimpScene, nullptr);
    
    // TODO: add assert scene incompete
    //if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
//        KitEngine::Core::Log::Error("Assimp load error: {}", importer.GetErrorString());
//    }
}

void Render::KitModel::ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, KitStaticMesh* parentMesh)
{
    KitStaticMesh* pParent = parentMesh; 

    // Обрабатываем все меши ноды
    for (uint32_t iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
    {
        // Получаем меш по индексу
        const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[iMesh]];

        KitStaticMesh& kitMesh = this->ProcessAssimpMesh(pMesh, pScene);
        kitMesh.SetHierarchyIcon("\xef\x86\xb2"); // TODO: fix it! cube icon

        pParent = &kitMesh;
        if (parentMesh == nullptr) {
            mChildren.emplace_back(pParent);
        } else {
            pParent->AddChild(pParent);
        }

    }

    // Рекурсивно обрабатываем все дочерние ноды
    for (uint32_t iChild = 0; iChild < pNode->mNumChildren; iChild++)
    {
        this->ProcessAssimpNode(pNode->mChildren[iChild], pScene, pParent);
    }
}


Render::KitStaticMesh& Render::KitModel::ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene)
{
    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    // Создаём вектор под вершины и резервируем место
    std::vector<KitVertex> vertices;
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
        vertices.emplace_back(KitVertex{
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

    // Создаём новый материал (по умолчанию)
    KitMaterial material;

    // Если на меш назначен материал, загружаем его
    if (pMesh->mMaterialIndex >= 0)
    {
        // Удаляем имя файла из пути, чтобы получить директорию
        std::filesystem::path directory = std::filesystem::path(mFilepath);
        directory.remove_filename();
        
        // Обрабатываем материал
        this->ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex], 
            directory.string(), material);
    }

    // Cоздаём новый объект
    auto obj = mAttachedObject.GetScene()->CreateObject();

    // Добавляем ему компонент меша
    auto& mesh = obj.AddComponent<KitStaticMesh>(obj);

    // Инициализируем меш
    mesh.Init(vertices, indices);

    // Сохраняем имя
    mesh.SetName(pMesh->mName.C_Str());

    // Сохраняем материал
    mesh.mMaterial = material;

    // Возвращаем меш
    return mesh;
}

void Render::KitModel::ProcessAssimpMaterial(const aiMaterial* pMaterial, const std::string& directory, 
    KitMaterial& kitMaterial)
{
    // Загружаем имя материала
    kitMaterial.mName = pMaterial->GetName().C_Str();

    // Загружаем diffuse текстуры 
    kitMaterial.diffuseTextures = this->LoadMaterialTextures(pMaterial, aiTextureType_DIFFUSE, directory);

}

std::vector<std::shared_ptr<Render::KitTexture>> Render::KitModel::LoadMaterialTextures(const aiMaterial* pMaterial, 
    aiTextureType type, const std::string& directory)
{
    // Создаём вектор под текстуры и резервируем место 
    std::vector<std::shared_ptr<KitTexture>> textures;
    textures.reserve(pMaterial->GetTextureCount(type));

    // Обходим все текстуры указанного типа
    for (uint32_t iTexture = 0; iTexture < pMaterial->GetTextureCount(type); iTexture++)
    {
        // Получаем имя текстуры
        aiString name;
        pMaterial->GetTexture(type, iTexture, &name);

        /*
        * Мы предпологаем, что текстура находится в той же директории, где и модель,
        * поэтому directory - это директория модели. 
        * Мы объединяем её с именем текстуры, чтобы получить предпологаемый путь. 
        */
        std::filesystem::path filepath = std::filesystem::path(directory);
        filepath.concat(name.C_Str());

        // Добавляем текстуру в список текстур
        textures.emplace_back(std::make_shared<KitTexture>(filepath.string(), 
            static_cast<KitTextureType>(type)));
    }

    // Возвращаем список загруженных текстур
    return textures;
}