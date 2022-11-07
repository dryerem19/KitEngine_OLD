//
// Created by dryerem19 on 11/2/22.
//

#ifndef LEVELEDITOR_MESHCOMPONENT_H
#define LEVELEDITOR_MESHCOMPONENT_H

#include <utility>

#include "KitEnginePch.h"
#include "Graphics/VertexArray.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/MeshEntry.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"

#include <kitVertex.h>

namespace KitEngine::Graphics::Components
{
    class ModelComponent
    {
    public:
        VertexArray                                                         mVertexArray;
        IndexBuffer                                                         mIndexBuffer;
        std::vector<MeshEntry>                                              mMeshes;

        ModelComponent(const VertexArray&                                   vertexArray,
                       const IndexBuffer&                                   indexBuffer,
                       std::vector<MeshEntry>                               meshes) :


                       mVertexArray     (vertexArray),
                       mIndexBuffer     (indexBuffer),
                       mMeshes          (std::move(meshes)) {

        }

        ModelComponent(const ModelComponent&) = default;
    };
}

#endif //LEVELEDITOR_MESHCOMPONENT_H
