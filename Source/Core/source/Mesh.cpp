/**
 * @file Mesh.cpp
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#include "pch.h"
#include "Mesh.h"

#include "RenderBackend.h"

#include "ResourceManager.h"

Mesh::Mesh(const std::vector<KitVertex>& vertices, 
    const std::vector<uint32_t>& indices)
{
    this->Init(vertices, indices);
}

Mesh::Mesh(const void* vertices, const uint32_t size,
            const uint32_t* indices, const uint32_t count)
{
    geometry.vbo.Init(vertices, size * sizeof(KitVertex));

    // Инициализация слоя буфера
    Render::VertexBufferLayout bufferLayout;
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(2);


    geometry.vao.AddBuffer(geometry.vbo, bufferLayout);

    geometry.ibo.Init(indices, count); 
}

void Mesh::Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>& indices)
{
    // Инициализация буфера вершин
    //mVertexBuffer.Init(vertices.data(), vertices.size() * sizeof(vertices[0]));

    geometry.vbo.Init(vertices.data(), vertices.size() * sizeof(vertices[0]));

    // Инициализация слоя буфера
    Render::VertexBufferLayout bufferLayout;
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(2);

    // Добавляем буфер в буфер вершин
    //mVertexArray.AddBuffer(mVertexBuffer, bufferLayout);

    geometry.vao.AddBuffer(geometry.vbo, bufferLayout);

    // Инициализация буфера индексов
    //mIndexBuffer.Init(indices.data(), indices.size());

    geometry.ibo.Init(indices.data(), indices.size());
} 

void Mesh::SetMaterial(const std::string& filepath)
{
    mMaterial = Core::ResourceManager::Instance().GetMaterial(filepath);
}