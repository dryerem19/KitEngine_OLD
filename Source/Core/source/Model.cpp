/**
 * @file Model.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Model.h"
#include "ResourceManager.h"

void Model::Deserialize(const std::string& filepath)
{
    KitModelFile kmf;
    kmf.Deserialize(filepath);

    mName = kmf.name;
    mAabb = kmf.mAABB;
    mFilepath = kmf.filepath;

    mMeshes.reserve(kmf.meshes.size());
    for (auto& mesh : kmf.meshes)
    {
        mMeshes.emplace_back(std::make_unique<Mesh>(mesh->vertices, mesh->indices));
        mMeshes.back()->name = mesh->name;
        mMeshes.back()->SetMaterial(mesh->material);
    }

    // btVector3 tmpTriangle[3];
    // pTempMesh = new btTriangleMesh(true, false);    
    // for (uint32_t iMesh = 0; iMesh < kmf.meshes.size(); iMesh++)
    // {
    //     for (uint32_t iTriangle = 0; iTriangle < kmf.meshes[iMesh]->indices.size(); iTriangle += 3)
    //     {
    //         for (uint32_t iVertex = 0; iVertex < 3; iVertex++)
    //         {
    //             int index = kmf.meshes[iMesh]->indices[iTriangle + iVertex];
    //             const auto& vertex = kmf.meshes[iMesh]->vertices[index];  

    //             tmpTriangle[iVertex].setX(vertex.mPosition.x);
    //             tmpTriangle[iVertex].setY(vertex.mPosition.x);
    //             tmpTriangle[iVertex].setZ(vertex.mPosition.x);           
    //         }
    //         pTempMesh->addTriangle(tmpTriangle[0], tmpTriangle[0], tmpTriangle[2], true);
    //     }
    // }

    // btVector3 aabbMin(-1000,-1000,-1000);
    // btVector3 aabbMax(1000,1000,1000);
    // pTempMesh->setPremadeAabb(aabbMin, aabbMax);
    // pTempMesh->setPremadeAabb(btVector3(kmf.mAABB.mMin.x, kmf.mAABB.mMin.y, kmf.mAABB.mMin.z),
    //     btVector3(kmf.mAABB.mMax.x, kmf.mAABB.mMax.y, kmf.mAABB.mMax.z));
}

void Model::Load(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filepath.c_str(),
                            aiProcess_GenSmoothNormals           |
                            aiProcess_ValidateDataStructure      |
                            aiProcess_CalcTangentSpace           |
                            aiProcess_FlipUVs                    |
                            aiProcess_RemoveRedundantMaterials   |
                            aiProcess_GenUVCoords                |
                            aiProcess_Triangulate                |
                            aiProcess_OptimizeMeshes             |
                            aiProcess_JoinIdenticalVertices      );

    if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    mDirectory = filepath.substr(0, filepath.find_last_of('/'));
}

void Model::ProcessNode(const aiNode *pNode, const aiScene *pScene)
{

}

std::shared_ptr<Mesh> Model::ProcessMesh(const aiMesh *pMesh, const aiScene *pScene)
{
    std::vector<KitVertex> vertices;
    vertices.reserve(pMesh->mNumVertices);

    std::vector<unsigned int> indices;
    indices.reserve(pMesh->mNumFaces * 3);

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    for (unsigned int iVertex = 0; iVertex < pMesh->mNumVertices; iVertex++)
    {
        const aiVector3D& position = pMesh->mVertices[iVertex];
        const aiVector3D& norcoord = pMesh->mNormals[iVertex];
        const aiVector3D& texcoord = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][iVertex] : zero3D;

        vertices.emplace_back(glm::vec3(position.x, position.y, position.z), 
                              glm::vec3(norcoord.x, norcoord.y, norcoord.z), glm::vec2(texcoord.x, texcoord.y));
    }

    for (unsigned int iFace = 0; iFace < pMesh->mNumFaces; iFace++)
    {
        const aiFace& face = pMesh->mFaces[iFace];
        indices.emplace_back(face.mIndices[0]);
        indices.emplace_back(face.mIndices[1]);
        indices.emplace_back(face.mIndices[2]);
    }

    if (pMesh->mMaterialIndex >= 0)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
    }
}

void Model::ProcessMaterial(const aiMaterial *pMaterial, const aiScene *pScene)
{
    Render::KitMaterial material;

    aiColor4D color(0.0f, 0.0f, 0.0f, 0.0f);
    float shininess;

    pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    material.SetDiffuse(glm::vec4(color.r, color.g, color.b, color.a));

    pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
    material.SetSpecular(glm::vec4(color.r, color.g, color.b, color.a));

    pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
    material.SetAmbient(glm::vec4(color.r, color.g, color.b, color.a));

    pMaterial->Get(AI_MATKEY_SHININESS, shininess);
    material.SetShininess(shininess);
}

std::vector<std::shared_ptr<Render::KitTexture>> Model::LoadTextures(const aiMaterial *pMaterial, aiTextureType type, const aiScene* pScene)
{
    std::vector<std::shared_ptr<Render::KitTexture>> textures;
    for (unsigned int iTexture = 0; iTexture < pMaterial->GetTextureCount(type); iTexture++)
    {
        aiString textureFile;
        if (AI_SUCCESS == pMaterial->GetTexture(type, iTexture, &textureFile))
        {
            if (const aiTexture* pTexture = pScene->GetEmbeddedTexture(textureFile.C_Str()))
            {

            }
            else
            {
                std::string texturePath = mDirectory + '/' + textureFile.C_Str();
                textures.emplace_back(Core::ResourceManager::Instance().GetTexture(texturePath));
            }
        }
    }

    return textures;
}

void Model::Draw(const std::shared_ptr<Shader>& shader, const BaseCamera& camera)
{
    for (auto& mesh : mMeshes)
    {
        glBindVertexArray(mesh->geometry.vao.GetId());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->geometry.ibo.id());

        const glm::mat4& model = mTransform.GetModelMatrix();
        const glm::mat4 mvp = model * camera.GetViewProjection();

        //shader.SetMat("u_mvp_matrix", mvp);
        //shader.SetMat("u_model_matrix", model);

        mesh->mMaterial->mShader->SetMat("u_mvp_matrix", mvp);
        mesh->mMaterial->mShader->SetMat("u_model_matrix", model);        
        
        glDrawElements(GL_TRIANGLES, mesh->geometry.ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
