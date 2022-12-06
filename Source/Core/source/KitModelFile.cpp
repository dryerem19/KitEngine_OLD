/**
 * @file KitModelFile.cpp
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
#include "pch.h"
#include "KitModelFile.h"


void KitModelFile::Serialize(const std::string& filepath)
{
    std::ofstream out(filepath, std::ios::binary);
    out.write((char*)&header, sizeof(header));

    size_t size_filepath = description.filepath.size();
    out.write((char*)&size_filepath, sizeof(size_filepath));
    out.write((char*)&description.filepath[0], size_filepath);

    size_t size_name = description.name.size();
    out.write((char*)&size_name, sizeof(size_name));
    out.write((char*)&description.name[0], size_name);

    /* Рекурсивно записываем узлы */
    auto leaf_recurse = [&](KMFNode* pKmfNode, auto&& leaf_recurse) -> void
    {
        WriteNode(out, pKmfNode);
        for (auto&& kmfChildNode : pKmfNode->children)
        {
            leaf_recurse(kmfChildNode.get(), leaf_recurse);
        }
    };
    
    if (root.get())
    {   
        leaf_recurse(root.get(), leaf_recurse);
    }

    out.close();
}

void KitModelFile::Deserialize(const std::string& filepath)
{
    std::ifstream input(filepath, std::ios::binary);
    input.read((char*)&header, sizeof(header));
    mIsValid = header.version == KMF_VERSION;
    if(!mIsValid)
    {
        return;
    }

    size_t size_filepath = 0;
    input.read((char*)&size_filepath, sizeof(size_t));
    description.filepath.resize(size_filepath);
    input.read((char*)&description.filepath[0], size_filepath);

    size_t size_name = 0;
    input.read((char*)&size_name, sizeof(size_t));
    description.name.resize(size_name);
    input.read((char*)&description.name[0], size_name);

    /* Рекурсивно считываем все узлы */
    auto leaf_recurse = [&](KMFNode* pParentKmfNode, auto&& leaf_recurse) -> void
    {
        assert(pParentKmfNode && "pParentKmfNode can't be a nullptr!");

        /* Считываем количетсво дочерних узлов */
        size_t size_children_nodes = 0;
        input.read(reinterpret_cast<char*>(&size_children_nodes), sizeof(size_children_nodes));
        pParentKmfNode->children.resize(size_children_nodes);             

        /* Считываем данные дочерних узлов */
        for (size_t iChildNode = 0; iChildNode < size_children_nodes; iChildNode++)
        {  
            /* Считываем дочерний узел */
            std::shared_ptr<KMFNode> kmfChildNode = ReadNode(input);

            /* Устанавливаем родственные связи */
            kmfChildNode->pParent = pParentKmfNode;   
            pParentKmfNode->children[iChildNode] = kmfChildNode;     

            /* Рекурсивно считываем дочерние узлы */                    
            leaf_recurse(kmfChildNode.get(), leaf_recurse);
        }        
    };    

    ReadRootNode(input);
    leaf_recurse(root.get(), leaf_recurse);

    input.close();
}

void KitModelFile::WriteMesh(std::ofstream& out, KMFMesh* pKmfMesh)
{
    assert(pKmfMesh && "pKmfMesh can't be a nullptr!");

    /* Записываем имя сетки */
    size_t size_mesh_name = pKmfMesh->name.size();
    out.write(reinterpret_cast<const char*>(&size_mesh_name), sizeof(size_mesh_name));
    out.write(reinterpret_cast<const char*>(&pKmfMesh->name[0]), size_mesh_name);

    /* Записываем путь к материалу */
    size_t size_material_name = pKmfMesh->material.size();
    out.write(reinterpret_cast<const char*>(&size_material_name), sizeof(size_material_name));
    out.write(reinterpret_cast<const char*>(&pKmfMesh->material[0]), size_material_name);

    /* Записываем данные индексов */
    size_t indices_size = pKmfMesh->indices.size();
    out.write(reinterpret_cast<const char*>(&indices_size), sizeof(indices_size));
    out.write(reinterpret_cast<const char*>(&pKmfMesh->indices[0]), indices_size * sizeof(pKmfMesh->indices[0]));

    /* Записываем данные вершин */
    size_t vertices_size = pKmfMesh->vertices.size();
    out.write(reinterpret_cast<const char*>(&vertices_size), sizeof(vertices_size));
    out.write(reinterpret_cast<const char*>(&pKmfMesh->vertices[0]), vertices_size * sizeof(pKmfMesh->vertices[0]));    
}

void KitModelFile::WriteNode(std::ofstream& out, KMFNode* pParentKmfNode)
{
    assert(pParentKmfNode && "pParentKmfNode can't be a nullptr!");
    
    /* Записываем название узла */
    size_t size_node_name = pParentKmfNode->name.size();
    out.write(reinterpret_cast<const char*>(&size_node_name), sizeof(size_node_name));
    out.write(reinterpret_cast<const char*>(&pParentKmfNode->name[0]), size_node_name);

    /* Записываем данные всех сеток */
    size_t size_meshes = pParentKmfNode->meshes.size();
    out.write(reinterpret_cast<const char*>(&size_meshes), sizeof(size_meshes));    
    for (auto&& mesh : pParentKmfNode->meshes)
    {
        WriteMesh(out, &mesh);
    }

    /* Записываем данные всех дочерних узлов */
    size_t size_children_nodes = pParentKmfNode->children.size();
    out.write(reinterpret_cast<const char*>(&size_children_nodes), sizeof(size_children_nodes));
}

void KitModelFile::ReadNodeMeshes(std::ifstream& input, KMFNode* pParentKmfNode)
{
    assert(pParentKmfNode && "pParentKmfNode can't be a nullptr!");

    /* Считываем количетсво сеток узла */
    size_t size_meshes = 0;
    input.read(reinterpret_cast<char*>(&size_meshes), sizeof(size_meshes));
    pParentKmfNode->meshes.resize(size_meshes); 

    /* Считываем данные сеток узла */
    for (size_t iMesh = 0; iMesh < size_meshes; iMesh++)
    {
        /* Считываем название сетки */
        size_t size_mesh_name = 0;
        input.read(reinterpret_cast<char*>(&size_mesh_name), sizeof(size_mesh_name));
        pParentKmfNode->meshes[iMesh].name.resize(size_mesh_name);
        input.read(reinterpret_cast<char*>(&pParentKmfNode->meshes[iMesh].name[0]), size_mesh_name);

        /* Считываем путь материала */
        size_t size_material_name = 0;
        input.read(reinterpret_cast<char*>(&size_material_name), sizeof(size_material_name));
        pParentKmfNode->meshes[iMesh].material.resize(size_material_name);
        input.read(reinterpret_cast<char*>(&pParentKmfNode->meshes[iMesh].material[0]), size_material_name);

        /* Считываем индексы сетки */
        size_t indices_size = 0;
        input.read(reinterpret_cast<char*>(&indices_size), sizeof(indices_size));
        pParentKmfNode->meshes[iMesh].indices.resize(indices_size);
        input.read(reinterpret_cast<char*>(&pParentKmfNode->meshes[iMesh].indices[0]), indices_size * sizeof(pParentKmfNode->meshes[iMesh].indices[0]));

        /* Считываем вершины сетки */
        size_t vertices_size = 0;
        input.read(reinterpret_cast<char*>(&vertices_size), sizeof(vertices_size));
        pParentKmfNode->meshes[iMesh].vertices.resize(vertices_size);
        input.read(reinterpret_cast<char*>(&pParentKmfNode->meshes[iMesh].vertices[0]), vertices_size * sizeof(pParentKmfNode->meshes[iMesh].vertices[0]));            
    }    
}

void KitModelFile::ReadRootNode(std::ifstream& input)
{
    root = std::make_unique<KMFNode>();

    /* Считываем название узла */
    size_t size_node_name = 0;
    input.read(reinterpret_cast<char*>(&size_node_name), sizeof(size_node_name));
    root->name.resize(size_node_name);
    input.read(reinterpret_cast<char*>(&root->name[0]), size_node_name);  

    /* Считываем сетки узла */
    ReadNodeMeshes(input, root.get());  
}

std::shared_ptr<KMFNode> KitModelFile::ReadNode(std::ifstream& input)
{
    /* Выделяем память для узла */
    std::shared_ptr<KMFNode> kmfChildNode = std::make_shared<KMFNode>();

    /* Считываем название узла */
    size_t size_node_name = 0;
    input.read(reinterpret_cast<char*>(&size_node_name), sizeof(size_node_name));
    kmfChildNode->name.resize(size_node_name);
    input.read(reinterpret_cast<char*>(&kmfChildNode->name[0]), size_node_name);
    
    /* Считываем сетки узла */
    ReadNodeMeshes(input, kmfChildNode.get()); 

    return kmfChildNode;
}