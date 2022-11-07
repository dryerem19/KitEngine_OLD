//
// Created by dryerem19 on 11/2/22.
//

#ifndef LEVELEDITOR_MESHCOMPONENT_H
#define LEVELEDITOR_MESHCOMPONENT_H

#include "Graphics/VertexArray.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"

#include <vector>

//#include <kitMesh.h>

#include <kitMesh.h>

namespace KitEngine::Graphics::Components
{
    class ModelComponent
    {
    public:
        VertexArray                                                         mVertexArray;
        IndexBuffer                                                         mIndexBuffer;
        std::vector<kitModelLoader::MeshEntry>                                              mMeshes;

        ModelComponent(const VertexArray&                                   vertexArray,
                       const IndexBuffer&                                   indexBuffer,
                       std::vector<kitModelLoader::MeshEntry>                               meshes) :


                       mVertexArray     (vertexArray),
                       mIndexBuffer     (indexBuffer),
                       mMeshes          (std::move(meshes)) {

        }

        ModelComponent(const ModelComponent&) = default;
    };
}

#endif //LEVELEDITOR_MESHCOMPONENT_H
