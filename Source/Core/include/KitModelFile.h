/**
 * @file KitModelFile.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"
#include "KitVertex.h"

#define KMF_VERSION 1

struct KMFHeader
{
    uint8_t version;
};

struct KMFDescription
{
    std::string filepath;
    std::string name;
};

struct KMFMesh final
{
    /* Имя сетки*/
    std::string name;

    /* Путь к материалу сетки */
    std::string material;

    /* Данные индексов сетки */
    std::vector<uint32_t> indices;

    /* Данные вершин сетки */
    std::vector<Render::KitVertex> vertices;
};

struct KMFNode final
{
    std::string name;

    KMFNode* pParent = nullptr;
    
    std::vector<KMFMesh> meshes;
    std::vector<std::shared_ptr<KMFNode>> children;

    KMFNode() = default;
    ~KMFNode() = default;
};

class KitModelFile final : private ISerialization, private IDeserialization
{
public:
    KMFHeader header;
    KMFDescription description;
    std::unique_ptr<KMFNode> root;

    void Serialize() override final;
    void Deserialize(const std::string& filepath) override final; 
    inline bool IsValid() const { return mIsValid; }
private:
    void WriteMesh(std::ofstream& out, KMFMesh* pKmfMesh);
    void WriteNode(std::ofstream& out, KMFNode* pParentKmfNode);
    void ReadNodeMeshes(std::ifstream& input, KMFNode* pParentKmfNode);
    void ReadRootNode(std::ifstream& input);
    std::shared_ptr<KMFNode> ReadNode(std::ifstream& input);
private:
    bool mIsValid = true;
};
