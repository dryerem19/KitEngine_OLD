/**
 * @file MeshComponent.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Mesh implementation
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(const std::vector<KitVertex> &vertices, const std::vector<uint32_t> &indices)
    : mVertexBufferObject(vertices.data(), vertices.size() * sizeof(vertices[0])), mIndexBufferObject(indices.data(), indices.size())
{
    VertexBufferLayout bufferLayout;
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(3);
    bufferLayout.AddFloatElement(2);
    mVertexArrayObject.AddBuffer(bufferLayout, bufferLayout);
}