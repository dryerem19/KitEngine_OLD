/**
 * @file MeshComponent.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Mesh interface
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "KitVertex.h"

class MeshComponent
{
private:
    VertexArray  mVertexArrayObject;
    VertexBuffer mVertexBufferObject;
    IndexBuffer  mIndexBufferObject;
public:
    MeshComponent(const std::vector<KitVertex>& vertices, const std::vector<uint32_t>& indices);
    const VertexBuffer& GetVertexBuffer() const { return mVertexBufferObject; }
    const IndexBuffer& GetIndexBuffer() const { return mIndexBufferObject; }
};