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
    std::ofstream out(filepath + ".kmf", std::ios::binary);

    out.write(reinterpret_cast<const char*>(&version), sizeof(version));
    
    size_t name_size = name.size();
    out.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));
    out.write(reinterpret_cast<const char*>(&name[0]), name_size);

    size_t size_meshes = meshes.size();
    out.write(reinterpret_cast<const char*>(&size_meshes), sizeof(size_meshes));
    for (auto& mesh : meshes)
    {
        /* Записываем имя сетки */
        size_t size_mesh_name = mesh->name.size();
        out.write(reinterpret_cast<const char*>(&size_mesh_name), sizeof(size_mesh_name));
        out.write(reinterpret_cast<const char*>(&mesh->name[0]), size_mesh_name);

        /* Записываем путь к материалу */
        size_t size_material_name = mesh->material.size();
        out.write(reinterpret_cast<const char*>(&size_material_name), sizeof(size_material_name));
        out.write(reinterpret_cast<const char*>(&mesh->material[0]), size_material_name);

        /* Записываем данные индексов */
        size_t indices_size = mesh->indices.size();
        out.write(reinterpret_cast<const char*>(&indices_size), sizeof(indices_size));
        out.write(reinterpret_cast<const char*>(&mesh->indices[0]), indices_size * sizeof(mesh->indices[0]));

        /* Записываем данные вершин */
        size_t vertices_size = mesh->vertices.size();
        out.write(reinterpret_cast<const char*>(&vertices_size), sizeof(vertices_size));
        out.write(reinterpret_cast<const char*>(&mesh->vertices[0]), vertices_size * sizeof(mesh->vertices[0]));
    }

    out.close();
}

void KitModelFile::Deserialize(const std::string& filepath)
{
    std::ifstream input(filepath, std::ios::binary);

    uint8_t read_version = 0;
    input.read((char*)&read_version, sizeof(read_version));
    if (read_version != version)
    {
        valid = false;
        return;
    }

    size_t name_size = 0;
    input.read((char*)&name_size, sizeof(name_size));
    name.resize(name_size);
    input.read((char*)&name[0], name_size);

    size_t size_meshes = 0;
    input.read((char*)&size_meshes, sizeof(size_meshes));
    meshes.reserve(size_meshes);
    for (size_t iMesh = 0; iMesh < size_meshes; iMesh++)
    {
        meshes.emplace_back(std::make_unique<KMFMesh>());

        /* Считываем название сетки */
        size_t size_mesh_name = 0;
        input.read(reinterpret_cast<char*>(&size_mesh_name), sizeof(size_mesh_name));
        meshes[iMesh]->name.resize(size_mesh_name);
        input.read(reinterpret_cast<char*>(&meshes[iMesh]->name[0]), size_mesh_name);

        /* Считываем путь материала */
        size_t size_material_name = 0;
        input.read(reinterpret_cast<char*>(&size_material_name), sizeof(size_material_name));
        meshes[iMesh]->material.resize(size_material_name);
        input.read(reinterpret_cast<char*>(&meshes[iMesh]->material[0]), size_material_name);

        /* Считываем индексы сетки */
        size_t indices_size = 0;
        input.read(reinterpret_cast<char*>(&indices_size), sizeof(indices_size));
        meshes[iMesh]->indices.resize(indices_size);
        input.read(reinterpret_cast<char*>(&meshes[iMesh]->indices[0]), indices_size * sizeof(meshes[iMesh]->indices[0]));

        /* Считываем вершины сетки */
        size_t vertices_size = 0;
        input.read(reinterpret_cast<char*>(&vertices_size), sizeof(vertices_size));
        meshes[iMesh]->vertices.resize(vertices_size);
        input.read(reinterpret_cast<char*>(&meshes[iMesh]->vertices[0]), vertices_size * sizeof(meshes[iMesh]->vertices[0])); 
    }

    input.close();
    valid = true;
    this->filepath = filepath;
}