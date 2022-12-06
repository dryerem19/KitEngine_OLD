/**
 * @file KitStaticMesh.cpp
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
#include "KitStaticMesh.h"

#include "RenderBackend.h"

Render::KitStaticMesh::KitStaticMesh(const KMFMesh& mesh)
{
    this->Init(mesh.vertices,mesh.indices);
}

Render::KitStaticMesh::KitStaticMesh(const std::vector<KitVertex>& vertices, 
    const std::vector<uint32_t>& indices)
{
    this->Init(vertices, indices);
}

void Render::KitStaticMesh::Init(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>& indices)
{
    // Инициализация буфера вершин
    //mVertexBuffer.Init(vertices.data(), vertices.size() * sizeof(vertices[0]));

    geometry.vbo.Init(vertices.data(), vertices.size() * sizeof(vertices[0]));

    // Инициализация слоя буфера
    VertexBufferLayout bufferLayout;
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

void Render::KitStaticMesh::Draw()
{
    // mVertexArray.Bind();
    // mIndexBuffer.Bind();

    //RenderBackend::Get().SetVAO(mVertexArray.GetId());
    //RenderBackend::Get().SetIBO(mIndexBuffer.id());

    RenderBackend::Get().SetGeometry(&geometry);

    //GLCall(glDrawElements(GL_TRIANGLES, mIndexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
    RenderBackend::Get().Render(geometry.ibo.GetCount());


    // mVertexArray.Unbind();
    // mIndexBuffer.Unbind();
}