//
// Created by dryerem19 on 11/2/22.
//

#ifndef LEVELEDITOR_MESHCOMPONENT_H
#define LEVELEDITOR_MESHCOMPONENT_H

#include <Renderer.h>

#include <vector>

//#include <kitMesh.h>

#include <kitMesh.h>

namespace KitEngine::Graphics::Components
{
    class ModelComponent
    {
    public:
        Render::VertexArray                                                         mVertexArray;
        Render::IndexBuffer                                                         mIndexBuffer;
        std::vector<kitModelLoader::MeshEntry>                                              mMeshes;

        ModelComponent(const Render::VertexArray&                                   vertexArray,
                       const Render::IndexBuffer&                                   indexBuffer,
                       std::vector<kitModelLoader::MeshEntry>                               meshes) :


                       mVertexArray     (vertexArray),
                       mIndexBuffer     (indexBuffer),
                       mMeshes          (std::move(meshes)) {

        }

        ModelComponent(const ModelComponent&) = default;
    };
}

#endif //LEVELEDITOR_MESHCOMPONENT_H
