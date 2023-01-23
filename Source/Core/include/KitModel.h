/**
 * @file KitModel.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-21
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "KitVertex.h"

struct KitMesh
{
    std::vector<Render::KitVertex> mVertices;
    std::vector<unsigned int> mIndices; 
};

class KitModel
{
private:
    struct MeshData
    {
        btTriangleMesh* m_bulletMesh;
        std::string mName;

        KitMesh mKitMesh;

        MeshData()
            : m_bulletMesh(nullptr) { }

        ~MeshData()
        {
            if (m_bulletMesh)
            {
                delete m_bulletMesh;
                m_bulletMesh = nullptr;
            }
        }
    };
    MeshData mRootMesh;
    std::string mFilepath;
public:
    KitModel(const std::string& filepath);
private:
    void Load();
    void ProccessNode(const aiNode* pNode, const aiScene* pScene);
    void ProccessMesh(const aiMesh* pMesh, const aiScene* pScene);
};