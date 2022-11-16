#include "RenderPch.h"
#include "KitModel.h"

Render::KitModel::KitModel(const std::string& filepath)
{
    this->Init(filepath);
}

void Render::KitModel::Init(const std::string& filepath)
{
    // Создаём объект импортера данных assimp'а
    Assimp::Importer importer;

    // Считываем данные файлы в сцену assimp'а
    const aiScene *pScene = nullptr;
    pScene = importer.ReadFile(filepath.c_str(),
                               aiProcess_GenSmoothNormals           |
                               aiProcess_ValidateDataStructure      |
                               aiProcess_CalcTangentSpace           |
                               aiProcess_FlipUVs                    |
                               aiProcess_RemoveRedundantMaterials   |
                               aiProcess_GenUVCoords                |
                               aiProcess_Triangulate                |
                               aiProcess_OptimizeMeshes             |
                               aiProcess_JoinIdenticalVertices      );

    // Обрабатываем все ноды сцены начиная с родительской
    mName = std::filesystem::path(pScene->mRootNode->mName.C_Str())
                                    .replace_extension("")
                                    .string();
    this->ProcessAssimpNode(pScene->mRootNode, pScene, filepath);
    
    // TODO: add assert scene incompete
    //if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
//        KitEngine::Core::Log::Error("Assimp load error: {}", importer.GetErrorString());
//    }
}

void Render::KitModel::ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, const std::string& filepath)
{
    // Обрабатываем все меши ноды
    for (uint32_t iMesh = 0; iMesh < pNode->mNumMeshes; iMesh++)
    {
        // Получаем меш по индексу
        const aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[iMesh]];
        mChildren.emplace_back(this->ProcessAssimpMesh(pMesh, pScene, filepath));
    }

    // Рекурсивно обрабатываем все дочерние ноды
    for (uint32_t iChild = 0; iChild < pNode->mNumChildren; iChild++)
    {
        this->ProcessAssimpNode(pNode->mChildren[iChild], pScene, filepath);
    }
}


std::shared_ptr<Render::KitStaticMesh> Render::KitModel::ProcessAssimpMesh(const aiMesh* pMesh, const aiScene* pScene, 
    const std::string& filepath)
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
        std::filesystem::path directory = std::filesystem::path(filepath);
        directory.remove_filename();
        
        // Обрабатываем материал
        this->ProcessAssimpMaterial(pScene->mMaterials[pMesh->mMaterialIndex], 
            directory.string(), material);
    }

    // Создаём новый меш
    std::shared_ptr<KitStaticMesh> kitMesh = std::make_shared<KitStaticMesh>();
    kitMesh->Init(vertices, indices); // Инициализируем его
    kitMesh->mName = pMesh->mName.C_Str(); // Загружаем имя меша
    kitMesh->mMaterial = material; // Устанавливаем материал

    // Возвращаем меш
    return kitMesh;
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