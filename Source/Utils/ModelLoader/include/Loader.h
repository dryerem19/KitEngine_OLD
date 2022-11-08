//
// Created by dryerem19 on 11/5/22.
//

#ifndef LEVELEDITOR_LOADER_H
#define LEVELEDITOR_LOADER_H

// Local includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "kitMaterial.h"
#include "kitMesh.h"
#include "kitVertex.h"

namespace kitModelLoader
{
    class Loader
    {
    public:
        std::vector<uint32_t>       mIndices;
        std::vector<MeshEntry>      mMeshes;
        std::vector<kitVertex>      mVertices;
        std::vector<kitMaterial>    mMaterials;

        Loader  ( ) = default;
        ~Loader ( ) = default;

        void Import (const std::filesystem::path& filepath);
        void Clear  ( );

    private:
        void InitScene                  (const aiScene* pScene, const std::filesystem::path& filepath);
        void CountVerticesAndIndices    (const aiScene* pScene, uint32_t& verticesCount, uint32_t& indicesCount);
        void ReserveSpace               (uint32_t& verticesCount, uint32_t& indicesCount);
        void InitAllMeshes              (const aiScene* pScene);
        void InitMesh                   (const aiMesh*  pMesh, const aiScene* pScene);
        void InitAllMaterials           (const aiScene* pScene, const std::filesystem::path& filepath);
        void InitMaterial               (const aiMaterial* pMaterial, const std::filesystem::path& filepath);
        static void InitTextures               (const aiMaterial* pMaterial, aiTextureType type, kitMaterial& material,
                                         const std::filesystem::path& filepath);
    };
}

#endif //LEVELEDITOR_LOADER_H
